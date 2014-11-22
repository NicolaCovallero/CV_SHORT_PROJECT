%% VIDEO READER EXAMPLE

video_obj=vision.VideoFileReader('TLRC_12sec.avi');
mov=vision.VideoFileWriter('D:\UPC\Computer Vision\Short_Project\CV_SHORT_PROJECT\myFile.avi','FrameRate',video_obj.info.VideoFrameRate);

k=1;
clear I;
while ~isDone(video_obj)
    % the function step get the frame indicated but the current object
    % index and move by a position the object index
    I=step(video_obj);  % four dimension because there are 3 channels for the colours 
    step(mov,I); % write the frame I in the video writer object MOV
    k=k+1;
end
release(video_obj); % we close the input/output stream 
release(mov);
