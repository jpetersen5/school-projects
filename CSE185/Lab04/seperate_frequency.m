function [low_pass_img, high_pass_img] = separate_frequency(img, ratio)
    % apply FFT
    frequency_map = fft2(img);
    
    % shift the frequency map
    frequency_map_shifted = fftshift(frequency_map);

    % compute low-frequency mask
    H = size(img,1);
    W = size(img,2);
    y1 = round(H/2 - ratio/2 * H);
    y2 = round(H/2 + ratio/2 * H);
    x1 = round(W/2 - ratio/2 * W);
    x2 = round(W/2 + ratio/2 * W);
    mask = zeros(size(img));
    mask(y1:y2, x1:x2, :) = 1;

    % separate low-frequency and high-frequency maps
    low_frequency_map_shifted = frequency_map_shifted .* mask;
    high_frequency_map_shifted = frequency_map_shifted .* (1 - mask);

    % shift frequency maps back
    low_frequency_map = ifftshift(low_frequency_map_shifted);
    high_frequency_map = ifftshift(high_frequency_map_shifted);

    % apply Inverse FFT
    low_pass_img = real(ifft2(low_frequency_map));
    high_pass_img = real(ifft2(high_frequency_map));
end