%% Lab Assignment 05, Task 2
% SSD
% load image and template
img1 = im2double(imread('einstein1.jpg'));
template = im2double(imread('template.jpg'));

% set threshold
threshold = 25;
% SSD
[output, match] = template_matching_SSD(img, template, threshold);

% write images
imwrite(output ./ max(output(:)), 'einstein1_ssd_output.jpg');
imwrite(match, 'einstein1_ssd_match.jpg');


% Normalized Cross-Correlation
% load image
img2 = im2double(imread('einstein2.jpg'));

% set threshold
threshold = 0.5;
% normcorr
[output, match] = template_matching_normcorr(img2, template, threshold);

% write images
imwrite(output ./ max(output(:)), 'einstein2_normcorr_output.jpg');
imwrite(match, 'einstein_normcorr_match.jpg');