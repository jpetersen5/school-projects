function output = sobel_filter(img, kernel)
    % intialize output image
    output = zeros(size(img));

    % pad original image
    % zero pad
    padded = zeros(size(img) + [2,2]);
    padded(2:size(padded)-1, 2:size(padded)-1, :) = img;
    % replication pad (comment out for just zero pad)
    % not made for kernel sizes besides 3, variable version in gaussian
    padded(1,:,:) = padded(2,:,:);
    padded(:,1,:) = padded(:,2,:);
    padded(size(padded),:,:) = padded(size(padded)-1,:,:);
    padded(:,size(padded),:) = padded(:,size(padded)-1,:);

    % loop through pixels
    for y = 2:size(padded, 2)-1
        for x = 2:size(padded, 1)-1
            % prepare value to assign pixel
            value = 0;
            % loop through kernel
            for ky = -1:1
                for kx = -1:1
                    value = value + kernel(kx+2,ky+2) * padded(x+kx,y+ky);
                end
            end
            % map to output image
            output(x-1, y-1) = value;
        end
    end
    
end