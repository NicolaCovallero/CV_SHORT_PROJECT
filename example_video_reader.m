%% VIDEO READER EXAMPLE

video_obj=vision.VideoFileReader('TLRC_12sec.avi');

figure;
for k=1:64
    subplot(8,8,k);
    % the function step get the frame indicated but the current object
    % index and move by a position the object index
    I(:,:,:,k)=step(video_obj);  % four dimension because there are 3 channels for the colours 
    imshow(I(:,:,:,k));
end

