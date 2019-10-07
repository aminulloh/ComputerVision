%COLOR HISTOGRAM EQUALIZATION

%READ THE INPUT IMAGE
I = imread('1.jpg');

%CONVERT THE RGB IMAGE INTO HSV IMAGE FORMAT
HSV = rgb2hsv(I);

%PERFORM HISTOGRAM EQUALIZATION ON INTENSITY COMPONENT
Heq = histeq(HSV(:,:,3));
Heq1 = histeq(HSV(:,:,2));

HSV_mod = HSV;
HSV_mod(:,:,3) = Heq;
HSV_mod(:,:,2) = Heq1;


RGB = hsv2rgb(HSV_mod);

figure(1)
subplot(1,2,1),imshow(I);title('Before Histogram Equalization');

subplot(1,2,2),imshow(RGB);title('After Histogram Equalization');  
       
%DISPLAY THE HISTOGRAM OF THE ORIGINAL AND THE EQUALIZED IMAGE

HIST_IN = zeros([256 3]);
HIST_OUT = zeros([256 3]);

%HISTOGRAM OF THE RED,GREEN AND BLUE COMPONENTS

HIST_IN(:,1) = imhist(I(:,:,1),256); %RED
HIST_IN(:,2) = imhist(I(:,:,2),256); %GREEN
HIST_IN(:,3) = imhist(I(:,:,3),256); %BLUE

HIST_OUT(:,1) = imhist(RGB(:,:,1),256); %RED
HIST_OUT(:,2) = imhist(RGB(:,:,2),256); %GREEN
HIST_OUT(:,3) = imhist(RGB(:,:,3),256); %BLUE

mymap=[1 0 0; 0.2 1 0; 0 0.2 1];
figure(2)
subplot(1,2,1),bar(HIST_IN);colormap(mymap);legend('RED CHANNEL','GREEN CHANNEL','BLUE CHANNEL');title('Before Applying Histogram Equalization');
subplot(1,2,2),bar(HIST_OUT);colormap(mymap);legend('RED CHANNEL','GREEN CHANNEL','BLUE CHANNEL');title('After Applying Histogram Equalization');