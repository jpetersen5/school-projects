%% Lab Assignment 02
% Load images
Ie = im2double(imread("einstein.jpg"));
If = im2double(imread("flowers.jpg"));
Il = im2double(imread("lena.jpg"));
Im = im2double(imread("marilyn.jpg"));
In = im2double(imread("new_york.jpg"));


%% Part 1
% seperate_frequency.m


%% Part 2
% set ratio
ratio = 0.1;
% call seperate_frequency
[lena_low_01,lena_high_01] = seperate_frequency(Il,ratio);
% write images
imwrite(lena_low_01, 'lena_low_0.1.jpg')
imwrite(lena_high_01 + 0.5, 'lena_high_0.1.jpg')


%% Part 3
% set ratio
ratio = 0.2;
% call seperate_frequency
[lena_low_02,lena_high_02] = seperate_frequency(Il,ratio);
% write images
imwrite(lena_low_02, 'lena_low_0.2.jpg')
imwrite(lena_high_02 + 0.5, 'lena_high_0.2.jpg')


%% Part 4
% hybrid_image.m


%% Part 5
% set ratio
ratio = 0.2;
% merge images with hybrid_image
img_merged_m_e = hybrid_image(Im, Ie, ratio);
% write image
imwrite(img_merged_m_e, 'hybrid_1.jpg');


%% Part 6
% set ratio
ratio = 0.2;
% merge images with hybrid_image
img_merged_e_m = hybrid_image(Ie, Im, ratio);
% write image
imwrite(img_merged_e_m, 'hybrid_2.jpg');