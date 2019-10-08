I = imread('air (1).jpg');

R = I(:,:,1);
G = I(:,:,2);
B = I(:,:,3);

histeq = histeq(I(:,:,1));
% HeqR = histeq(I);
% HeqG = histeq(G);
% HeqB = histeq(B);

HIST_IN = zeros([256 3]);
HIST_OUT = zeros([256 3]);

HIST_IN(:,1) = imhist(I(:,:,1),256); %RED
HIST_IN(:,2) = imhist(I(:,:,2),256); %GREEN
HIST_IN(:,3) = imhist(I(:,:,3),256); %BLUE

mymap=[1 0 0; 0.2 1 0; 0 0.2 1];

figure,bar(HIST_IN);colormap(mymap);
legend('RED CHANNEL','GREEN CHANNEL','BLUE CHANNEL');
title('Before Applying Histogram Equalization');