img1 = imread('01.jpg');

forwardrotate = zeros(300, 400, 3, 'uint8');

x0 = 150;
y0 = 200;

for x1 = 1:400
    for y1 = 1:300

        y2 = -sind(45) * (x1 - x0) + cosd(45) * (y1 - y0) + y0;
        x2 = cosd(45)*(x1 - x0) + sind(45)*(y1 - y0) + x0;

        x2 = round(x2);
        y2 = round(y2);

        if((x2 > 0) && (x2 <= 400)) && ((y2 > 0) && (y2 <= 300))
            forwardrotate(y2,x2,:) = img1(y1,x1,:);
        end
    end
end



figure, imshow(forwardrotate);

imwrite(forwardrotate, 'rotate_0test.jpg');
