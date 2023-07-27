function img_merged = hybrid_image(img1, img2, ratio)
    % split img1 and img2 into low/high frequency maps
    [img1low, ~] = seperate_frequency(img1,ratio);
    [~, img2high] = seperate_frequency(img2,ratio);
    % combine the low-frequency map of img1 with the high-frequency map of img2
    img_merged = img1low + img2high;
end