const std = @import("std");
const fs = std.fs;

pub const BrainfuckError = error{
    UnclosedBracket,
};

/// Embedded BF interface
pub const Brainfuck = struct {
    tape: []u8,

    /// Initialize a tape with a given `length` and `allocator`.
    pub fn init(length: usize, allocator: std.mem.Allocator) !Brainfuck {
        const tape = try allocator.alloc(u8, length);
        @memset(tape, 0);

        return Brainfuck{ .tape = tape };
    }

    /// De-initialize a tape with the same `allocator`.
    pub fn deinit(self: *Brainfuck, allocator: std.mem.Allocator) void {
        allocator.free(self.tape);
    }

    /// Execute a given `string`.
    pub fn executeString(self: *Brainfuck, string: []const u8) !void {
        try interpret(self, string);
    }

    /// Execute a given file at `path`.
    pub fn executeFile(self: *Brainfuck, path: []const u8) !void {
        var gp = std.heap.GeneralPurposeAllocator(.{ .safety = true }){};
        defer _ = gp.deinit();
        const allocator = &gp.allocator();

        var path_buffer: [fs.MAX_PATH_BYTES]u8 = undefined;
        const abs_path = try fs.realpath(path, &path_buffer);

        const file = try fs.openFileAbsolute(abs_path, .{});
        defer file.close();

        const file_size = (try file.stat()).size;
        const file_buffer = try allocator.alloc(u8, file_size);
        defer allocator.free(file_buffer);

        try file.reader().readNoEof(file_buffer);

        // interpret the file
        try interpret(self, file_buffer);
    }

    /// Get a cell at the given `index`.
    pub fn getCell(self: *Brainfuck, index: usize) !u8 {
        return try self.tape[index];
    }

    /// Internal function, to check for any unclosed brackets.
    fn syntaxErrorChecking(string: []const u8) bool {
        var there_are_brackets: u32 = 0;
        var pc: u32 = 0;

        while (string.len != pc) : (pc += 1) {
            if (string[pc] == '[') there_are_brackets += 1;
            if (string[pc] == ']') there_are_brackets -= 1;
        }

        if (there_are_brackets != 0) return true else return false;
    }

    /// An internal function uses a basic interpreter to run the code.
    fn interpret(self: *Brainfuck, string: []const u8) !void {
        const stdout = std.io.getStdOut().writer();
        const stdin = std.io.getStdIn().reader();

        if (syntaxErrorChecking(string) == true) {
            return BrainfuckError.UnclosedBracket;
        }

        var pointer: usize = 0;
        var pc: usize = 0;

        while (string.len != pc) : (pc += 1) {
            switch (string[pc]) {
                '+' => {
                    self.tape[pointer] +%= 1;
                },
                '-' => {
                    self.tape[pointer] -%= 1;
                },
                '>' => {
                    if (pointer >= self.tape.len) pointer = 0 else pointer += 1;
                },
                '<' => {
                    if (pointer == 0) pointer = self.tape.len - 1 else pointer -= 1;
                },
                '.' => {
                    _ = try stdout.writeByte(self.tape[pointer]);
                },
                ',' => {
                    self.tape[pointer] = try stdin.readByte();
                },
                '[' => {
                    if (self.tape[pointer] == 0) {
                        var loop: u32 = 1;
                        while (loop > 0) {
                            pc += 1;
                            if (string[pc] == '[') loop += 1;
                            if (string[pc] == ']') loop -= 1;
                        }
                    }
                },
                ']' => {
                    if (self.tape[pointer] != 0) {
                        var loop: u32 = 1;
                        while (loop > 0) {
                            pc -= 1;
                            if (string[pc] == '[') loop -= 1;
                            if (string[pc] == ']') loop += 1;
                        }
                    }
                },
                else => continue,
            }
        }
    }
};
