%% Lab Assignment 05, Task 2
% SSD
% load image and template
name = 'einstein2';
img = im2double(imread(sprintf('%s.jpg', name)));
template = im2double(imread('template.jpg'));

% set threshold
threshold = 25;
% SSD
[output, match] = template_matching_SSD(img, template, threshold);

% write images
imwrite(output ./ max(output(:)), sprintf('%s_ssd_output.jpg', name));
imwrite(match,  sprintf('%s_ssd_match.jpg', name));


% Normalized Cross-Correlation
% set threshold
threshold = 0.5;
% normcorr
[output, match] = template_matching_normcorr(img, template, threshold);

% write images
imwrite(output ./ max(output(:)), sprintf('%s_normcorr_output.jpg', name));
imwrite(match,  sprintf('%s_normcorr_match.jpg', name));