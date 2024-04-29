const std = @import("std");
const brainfuck = @import("brainfuck.zig").Brainfuck;

pub fn main() !void {
    const allocator = std.heap.page_allocator;
    var bf = try brainfuck.init(1024, allocator);
    defer bf.deinit(allocator);

    try bf.executeString(">++++++++[<++++++++>-]<+.");
    const value = try bf.getCell(0);
    std.debug.print("\n{c}\n", .{value});
}
