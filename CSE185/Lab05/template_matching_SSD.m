function [output, match] = template_matching_SSD(img, template, threshold)
    % initialize output image
    output = img;
    % set shift sizes
    shift_u = floor(size(template, 2) / 2);
    shift_v = floor(size(template, 1) / 2);

    % zero pad
    padded = zeros(size(img) + size(template) - 1);
    padded(1+shift_u:size(padded,1)-shift_u, 1+shift_v:size(padded,2)-shift_v, :) = img;
    % replication pad (comment out for just zero pad)
    for r = 1:shift_u
        % this loops through all the rows / columns of 0's and copies the
        % edge row / column until all is filled out
        padded(r,:,:) = padded(shift_u+1,:,:);
        padded(size(padded,1)+1-r,:,:) = padded(size(padded,1)-shift_u,:,:);
    end
    for r = 1:shift_v
        padded(:,r,:) = padded(:,shift_v+1,:);
        padded(:,size(padded,2)+1-r,:) = padded(:,size(padded,2)-shift_v,:);
    end

    for u = 1 + shift_u : size(padded, 2) - shift_u
        for v = 1 + shift_v : size(padded, 1) - shift_v
            % create patch boundaries to compare to template
            x1 = u - shift_u; x2 = u + shift_u;
            y1 = v - shift_v; y2 = v + shift_v;
            patch = padded(y1:y2, x1:x2);

            % SSD calculation
            value = sum(sum((patch - template).^2));

            % assign value to output image
            output(v - shift_v, u - shift_u) = value;

        end
    end

    match = (output < threshold);
end