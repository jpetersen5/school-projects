%% Lab Assignment 02
% Load image
img = im2double(imread("lena.jpg"));


%% Part 1
% Sobel filter (horizontal edge)
H = [1, 2, 1; 0, 0, 0; -1, -2, -1];
% process through filter
sobel1 = sobel_filter(img, H);
% figure, imshow(sobel1);
% write image
imwrite(sobel1, 'sobel_h.jpg');


%% Part 2
% Sobel filter (vertical edge)
H = [1, 0, -1; 2, 0, -2; 1, 0, -1];
% process through filter
sobel2 = sobel_filter(img, H);
% figure, imshow(sobel2);
% write image
imwrite(sobel2, 'sobel_v.jpg');


%% Part 3
% Gaussian filter
% set gaussian filter parameters
hsize = 5; sigma = 2;
% process through filter
gauss1 = gaussian_filter(img, hsize, sigma);
% figure, imshow(gauss1);
% write image
imwrite(gauss1, 'gaussian_5.jpg');


%% Part 4
% Gaussian filter
% set gaussian filter parameters
hsize = 9; sigma = 4;
% process through filter
gauss2 = gaussian_filter(img, hsize, sigma);
% figure, imshow(gauss2);
% write image
imwrite(gauss2, 'gaussian_9.jpg');