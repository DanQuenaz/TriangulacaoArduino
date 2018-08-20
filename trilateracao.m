clc
clear all

ax = 38.5;
ay = 23.7;

bx = 41.2;
by = 62.8;

cx = 52.5;
cy = 58.1;

px = 45.5;
py = 45.8;

euclidDist(px, py, ax, ay)
euclidDist(px, py, bx, by)
euclidDist(px, py, cx, cy)

hold on;
plot(ax, ay, ".");
plot(bx, by, ".");
plot(cx, cy, ".");
plot(px, py, ".");