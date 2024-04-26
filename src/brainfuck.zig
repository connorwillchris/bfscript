const std = @import("std");
const fs = std.fs;

pub const Brainfuck = struct {
    tape: []u8,

    pub fn init(length: usize, allocator: std.mem.Allocator) !Brainfuck {
        const tape = try allocator.alloc(u8, length);
        @memset(tape, 0);

        return Brainfuck{ .tape = tape };
    }

    pub fn deinit(self: *Brainfuck, allocator: std.mem.Allocator) void {
        allocator.free(self.tape);
    }

    pub fn executeString(self: *Brainfuck, string: []const u8) !void {
        try interpret(self, string);
    }

    //pub fn executeFile(self: *Brainfuck, path: []const u8) !void {}

    pub fn getCell(self: *Brainfuck, index: usize) !u8 {
        return self.tape[index];
    }

    fn interpret(self: *Brainfuck, string: []const u8) !void {
        const stdout = std.io.getStdOut().writer();
        const stdin = std.io.getStdIn().reader();

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
                    pointer += 1;
                },
                '<' => {
                    pointer -= 1;
                },
                '.' => {
                    _ = try stdout.writeByte(self.tape[pointer]);
                },
                ',' => {
                    self.tape[pointer] = try stdin.readByte();
                },
                '[' => {
                    if (self.tape[pointer] != 0) {
                        //continue;
                    }
                },
                ']' => {
                    if (self.tape[pointer] != 0) {
                        //while (string[pc] != '[') {
                        //    pc -= 1;
                        //}
                    }
                },
                else => continue,
            }
        }
    }
};
