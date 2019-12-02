clc;    % Clear the command window.
close all;  % Close all figures (except those of imtool.)
imtool close all;  % Close all imtool figures.
clear;  % Erase all existing variables.
workspace;  % Make sure the workspace panel is showing.
format long g;
format compact;
fontSize = 11;

rgbImage = imread('2.jpg');
% Get the dimensions of the image.  numberOfColorBands should be = 3.
[rows, columns, numberOfColorBands] = size(rgbImage);
% Display the original color image.
subplot(2, 2, 1);
imshow(rgbImage, []);
axis on;
caption = sprintf('Original Color Image, %d rows by %d columns.', rows, columns);
title(caption, 'FontSize', fontSize);
% Enlarge figure to full screen.
set(gcf, 'units','normalized','outerposition',[0, 0, 1, 1]);

% Let's get our template by extracting a small portion of the original image.
templateWidth = 71
templateHeight = 49
smallSubImage = imread('2a.jpg');
% Get the dimensions of the image.  numberOfColorBands should be = 3.
[rows, columns, numberOfColorBands] = size(smallSubImage);
subplot(2, 2, 2);
imshow(smallSubImage, []);
axis on;
caption = sprintf('Template Image to Search For, %d rows by %d columns.', rows, columns);
title(caption, 'FontSize', fontSize);

% Find out where the normalized cross correlation image is brightest.
[maxCorrValue, maxIndex] = max(abs(correlationOutput(:)));
[yPeak, xPeak] = ind2sub(size(correlationOutput),maxIndex(1))
% Because cross correlation increases the size of the image, 
% we need to shift back to find out where it would be in the original image.
corr_offset = [(xPeak-size(smallSubImage,2)) (yPeak-size(smallSubImage,1))]

% Plot it over the original image.
subplot(2, 2, 4); % Re-display image in lower right.
imshow(rgbImage);
axis on; % Show tick marks giving pixels
hold on; % Don't allow rectangle to blow away image.
% Calculate the rectangle for the template box.  Rect = [xLeft, yTop, widthInColumns, heightInRows]
boxRect = [corr_offset(1) corr_offset(2) templateWidth, templateHeight]
% Plot the box over the image.
rectangle('position', boxRect, 'edgecolor', 'g', 'linewidth',2);
% Give a caption above the image.
title('Template Image Found in Original Image', 'FontSize', fontSize);

