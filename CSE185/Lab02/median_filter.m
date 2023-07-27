w% median filter with variable patch size
function output = median_filter(img, patch_size)
    % intialize output image
    output = zeros(size(img));
    % set shift sizes based on patch size
    shift_u = floor(patch_size(1) / 2);
    shift_v = floor(patch_size(2) / 2);
    % loop through pixels, ignoring border pixels
    for u = (1 + shift_u):(size(img, 2) - shift_u)
        for v = (1 + shift_v):(size(img, 1) - shift_v)
            % set patch ranges based on shift amount
            x1 = u - shift_u; x2 = u + shift_u;
            y1 = v - shift_v; y2 = v + shift_v;
            % submatrix patch
            patch = img(y1:y2, x1:x2);
            % convert matrix to vector
            patch = patch(:);
            % median of patch
            value = median(patch);
            % assign to output image
            output(v, u) = value;
        end
    end
end