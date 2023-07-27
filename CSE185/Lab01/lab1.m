% preload images
I01 = imread("01.jpg");
I02 = imread("02.jpg");
I03 = imread("03.jpg");
I04 = imread("04.jpg");
I05 = imread("05.jpg");
I06 = imread("06.jpg");


% Part 1
% green channel to 0
G = I01;
G(:,:,2) = 0;
% save image
imwrite(G, "green.jpg")


% Part 2
% calculate the grayscale
Y = 0.299 * I01(:,:,1) + 0.587 * I01(:,:,2) + 0.114 * I01(:,:,3);
% save image
imwrite(Y, "gray.jpg")


% Part 3
% rotate 90 degrees
R = imrotate(I01, 90);
% save image
imwrite(R, "rotate.jpg")


% Part 4
% extract submatrix (crop)
C = I01(30:270, 100:300, :);
% save image
imwrite(C, "crop.jpg")


% Part 5
% flip image
F = flip(I01,2);
% save image
imwrite(F, "flip.jpg")


% Part 6
% create canvas
canvas = zeros(300 * 2 + 10, 400 * 2 + 10, 3, 'uint8');
% assign images to submatrices
canvas(1:300, 1:400, :) = I01;
canvas(1:300, 411:810, :) = I02;
canvas(311:610, 1:400, :) = I03;
canvas(311:610, 411:810, :) = I04;
% save image
imwrite(canvas,"combine.jpg")


% Part 7
% get image size (for returning to image)
sz = size(I05);
% images into vectors
V05 = I05(:);
V06 = I06(:);
% average two vectors
A = (V05 + V06) / 2;
% vector into image
A = reshape(A, sz(1), sz(2), sz(3));
% save image
imwrite(A,"average.jpg")
