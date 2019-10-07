clc;
clear;

x=imread('Picture1.jpg');
xg=rgb2gray(x);
xd=double(xg);
% xdm=mean(mean(xd));
% xd=xd-xdm;

h1=imread('mh.jpg');
h2=rgb2gray(h1);
hd=double(h2);
h3=hd/sum(sum(hd));
hm=mean(mean(h3));
h=h3-hm;

yd=filter2(h,xd);
ymax=max(max(yd));
y1=yd*255/ymax;
y=uint8(y1);

th=0.5;
y2=(yd>=th*ymax);
y3=yd.*y2;
y4=y3*255/ymax;
y5=uint8(y4);

u=[xg y y5];
imshow(u);
