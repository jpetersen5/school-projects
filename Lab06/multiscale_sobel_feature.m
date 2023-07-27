function feature = multiscale_sobel_feature(img, scale)
    % initialize feature vector
    feature = [];
    for i = 1:scale
        % compute sobel feature
        %[f, ~] = sobel_feature(img); % magnitude
        [~, f] = sobel_feature(img); % orientation
        % concatenate feature vector
        feature = cat(1, feature, f(:));
        % down-sample image by 2
        img = imresize(img,1/2);
    end
end