
i = imread('2.jpg');
f = rgb2gray(i);
figure,imshow(f),title('Frame Image')

j = imread('2a.jpg');
t = rgb2gray(j);
figure,imshow(t),title('Template Image')
S = SSDXCORR(f,t);

