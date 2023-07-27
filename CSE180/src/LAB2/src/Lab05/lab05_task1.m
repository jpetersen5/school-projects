%% Lab Assignment 05, Task 1
% Load image
img = im2double(imread('lena.jpg'));

% set specifications
sigma = 2.0;
hsize = 7;
scale = 5;


% Gaussian Pyramid
img_gp = img;
for s = 1 : scale
    % Gaussian filter
    img_gp = imfilter(img_gp,fspecial('gaussian',hsize,sigma),'replicate');

    % Save image
    imwrite(img_gp, sprintf('Gaussian_scale%d.jpg', s));

    % Down-sampling
    img_gp = imresize(img_gp,1/2);
end


% Laplacian Pyramid
img_lp = img;
for s = 1 : scale
    % Gaussian filtering
    img_lp_g = imfilter(img_lp,fspecial('gaussian',hsize,sigma));

    % Laplacian filtering
    img_lp_h = img_lp - img_lp_g;

    % Save or show image
    imwrite(img_lp_h + 0.5, sprintf('Laplacian_scale%d.jpg', s));

    % Down-sampling
    img_lp = imresize(img_lp,1/2);
end