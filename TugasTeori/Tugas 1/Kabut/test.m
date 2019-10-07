    d = 20
    p = 20
    f = figure;
    k=1;
    while k
    waitforbuttonpress;
    if get(gcf,'CurrentCharacter')==28 %left arrow key
    d=d-10
    elseif get(gcf,'CurrentCharacter')==29 %right arrow key
    d=d+10
    elseif get(gcf,'CurrentCharacter')==31 %down arrow key
    p=p-10
    elseif get(gcf,'CurrentCharacter')==30 %up arrow key
    p=p+10
    elseif get(gcf,'CurrentCharacter')==32 %space bar
    break
    end
    cla reset
    axis([-400,400,-200,200]);
    hold on
    ax = gca;
    ax.XTick = [];
    ax.YTick = [];
    ax.DataAspectRatioMode = 'manual';
    ax.DataAspectRatio = [1 1 1];
    ax.PlotBoxAspectRatioMode = 'manual';
    ax.PlotBoxAspectRatio = [1 1 1];
    img = imread('kabut (1).jpg');
    image([d -p],[d -p],img);
    end