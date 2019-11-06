clear
vid=videoinput('winvideo',1,'YUY2_320X240');
preview(vid)
 
for i=1:40
    a=getsnapshot(vid);
    b=ycbcr2rgb(a);
    c=rgb2gray(b);
    subplot(5,8,i), imshow(d)
end
stoppreview(vid)
delete(vid)
