const std = @import("std");
const brainfuck = @import("brainfuck.zig").Brainfuck;

pub fn main() !void {
    const allocator = std.heap.page_allocator;
    var bf = try brainfuck.init(30_000, allocator);
    defer bf.deinit(allocator);

    const sixty_five = "++++++++++.";

    try bf.executeString(sixty_five);
    //try bf.executeFile("C:\\Users\\Connor\\Dev\\bfscript\\tests\\test.bf");
    std.debug.print("Cell {d}: {d}\n", .{ 0, try bf.getCell(0) });
}
