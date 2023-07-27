function output = gaussian_filter(img, hsize, sigma)
    % H = fspecial('gaussian', hsize, sigma);

    % intialize output image
    output = zeros(size(img));
    % set shift size
    shift = floor(hsize(1) / 2);

    % create gaussian kernel
    % create two square matrices filled from -shift to shift horizontally
    % and vertically. these are equivalent to delta x and delta y in eq.
    [dx,dy] = meshgrid(-shift:shift);
    % equation from slides
    g = exp(-(dx.^2 + dy.^2) / (2 * sigma^2));
    % normalize
    H = g ./ sum(g(:));

    % zero pad
    padded = zeros(size(img) + [hsize-1,hsize-1]);
    padded(1+shift:size(padded)-shift, 1+shift:size(padded)-shift, :) = img;
    % replication pad (comment out for just zero pad)
    for r = 1:shift
        % this loops through all the rows / columns of 0's and copies the
        % edge row / column until all is filled out
        padded(r,:,:) = padded(shift+1,:,:);
        padded(:,r,:) = padded(:,shift+1,:);
        padded(size(padded)+1-r,:,:) = padded(size(padded)-shift,:,:);
        padded(:,size(padded)+1-r,:) = padded(:,size(padded)-shift,:);
    end

    % loop through pixels
    for u = 1+shift:size(padded, 2)-shift
        for v = 1+shift:size(padded, 1)-shift
            % prepare value to assign pixel
            value = 0;
            % loop through kernel
            for ky = 0-shift:shift
                for kx = 0-shift:shift
                    value = value + H(kx+shift+1,ky+shift+1) * padded(v+kx,u+ky);
                end
            end
            % assign to output image
            output(v-shift, u-shift) = value;
        end
    end

end