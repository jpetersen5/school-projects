%% Lab Assignment 02
% Load images
I01 = imread("01.jpg");
ILn = im2double(imread("lena_noisy.jpg"));


%% Part 1
% prepare new image
Ir0 = zeros(300,400,3,'uint8');
% rotation amount (in degrees)
rot = 45;
% origin (center of image)
y0 = 151;
x0 = 201;
% loop through pixels to rotate in original image
for y1 = 1:300
    for x1 = 1:400
        % calculate new rotated coordinates (forward)
        y2 = -sind(rot) * (x1-x0) + cosd(rot) * (y1-y0) + y0;
        x2 = cosd(rot) * (x1-x0) + sind(rot) * (y1-y0) + x0;
        % round to integer
        y2 = round(y2);
        x2 = round(x2);
        % check for inside boundaries
        if ((x2 > 0) && (x2 <= 400)) && ((y2 > 0) && (y2 <= 300))
            Ir0(y2,x2,:) = I01(y1,x1,:);
        end
    end
end
% write image
imwrite(Ir0,"rotate_0.jpg")


%% Part 2
% prepare new image
Ir1 = zeros(300,400,3,'uint8');
% rotation amount (in degrees)
rot = 45;
% origin (center of image)
y0 = 151;
x0 = 201;
% loop through pixels to map rotated image to
for y2 = 1:300
    for x2 = 1:400
        % calculate new rotated coordinates (backward)
        y1 = sind(rot) * (x2-x0) + cosd(rot) * (y2-y0) + y0;
        x1 = cosd(rot) * (x2-x0) - sind(rot) * (y2-y0) + x0;
        % round to integer
        y1 = round(y1);
        x1 = round(x1);
        % check for inside boundaries
        if ((x1 > 0) && (x1 <= 400)) && ((y1 > 0) && (y1 <= 300))
            Ir1(y2,x2,:) = I01(y1,x1,:);
        end
    end
end
% write image
imwrite(Ir1,"rotate_1.jpg")


%% Part 3
% patch size
patch3 = [3,3];
% process through median filter
ILnM3 = median_filter(ILn,patch3);
% write image
imwrite(ILnM3,"median_0.jpg")


%% Part 4
% patch size
patch5 = [5,5];
% process through median filter
ILnM5 = median_filter(ILn,patch5);
imwrite(ILnM5,"median_1.jpg")