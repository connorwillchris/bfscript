const std = @import("std");

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

    pub fn getCell(self: *Brainfuck, index: usize) !u8 {
        return self.tape[index];
    }
};

pub fn main() !void {
    const allocator = std.heap.page_allocator;
    var bf = try Brainfuck.init(30_000, allocator);
    defer bf.deinit(allocator);

    const sixty_five = ">++++++++[<++++++++>-]<+.";

    try bf.executeString(sixty_five);
    std.debug.print("Cell {d}: {d}\n", .{ 0, try bf.getCell(0) });
}
