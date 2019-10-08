clc;
clear all;

y = imread('kabut (10).jpg');
imhist(rgb2gray(y));
ymin=min(min(y));
ymax=max(max(y));
ymmin=mean(mean(ymin));
ymmax=mean(mean(ymax));
 
y1=255/(ymmax-ymmin)*(y-ymmin);
y1min=min(min(y1));
y1max=max(max(y1));
y1mmin=mean(mean(y1min));
y1mmax=mean(mean(y1max));

subplot(2,2,1);
imshow(y);
h = gca;
h.Visible = 'On';
title('Original Image');

subplot(2,2,2), 
imshow(y1),
h = gca;
h.Visible = 'On';
title('Auto-level Image');

subplot(2,2,3), imhist(rgb2gray(y)), title('Original Histogram');
text(10,3300,sprintf('Min=%.2f and Max=%.2f',ymmin, ymmax));

subplot(2,2,4), imhist(rgb2gray(y1)), title('Autolevel Histogram');
text(10,3100,sprintf('Min=%.2f and Max=%.2f',y1mmin, y1mmax));
