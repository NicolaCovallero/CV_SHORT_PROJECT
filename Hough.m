%% HOUGH LINE -- EXAMPLE

clear all; close all;

video_obj=vision.VideoFileReader('TLRC_12sec.avi');
frame_rate=video_obj.info.VideoFrameRate;
mov=vision.VideoFileWriter('D:\UPC\Computer Vision\Short_Project\CV_SHORT_PROJECT\video_Hough.avi','FrameRate',video_obj.info.VideoFrameRate);


h=1;
%while ~isDone(video_obj)
tic
while h<=1  
    I=step(video_obj);
    I=rgb2gray(I);
    BW=edge(I,'canny',100/255); %threshold of 100
    [H,T,R] = hough(BW);
    %imshow(H,[],'XData',T,'YData',R,...
    %    'InitialMagnification','fit');
    %xlabel('\theta'), ylabel('\rho');
    %axis on, axis normal, hold on;
    P  = houghpeaks(H,5,'threshold',ceil(0.3*max(H(:))));
    x = T(P(:,2)); y = R(P(:,1));
    %plot(x,y,'s','color','white');
    
    % Find lines and plot them
    lines = houghlines(BW,T,R,P,'FillGap',5,'MinLength',7);
    number_lines=size(lines,2);
    
    n=1;
    while ( n <= number_lines )
        if  lines(n).theta == 90 | lines(n).theta == -90 | lines(n).theta == 0
            lines(n) = [];
            number_lines = size(lines,2);
            n = n-1;
        end
        n=n+1;
    end
    
    
    %figure, imshow(I), hold on
    figure('visible','off'); imshow(I); hold on
    for k = 1:length(lines)
        % plotting line
        xy = [lines(k).point1; lines(k).point2];
        plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
    end
    I = (zbuffer_cdata(gcf));
    %step(mov,I); % write the frame I in the video writer object MOV
    h=h+1
end
toc
release(video_obj); % we close the input/output stream
release(mov);
