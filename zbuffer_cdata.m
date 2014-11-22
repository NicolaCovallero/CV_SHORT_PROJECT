function cdata = zbuffer_cdata(hfig)
% function to get from a figure the image showed without pop it up the
% getting image. Note usually to do one would use the function getframe
% but this function pops up the gotten image. 
% From: 
%       http://www.mathworks.com/matlabcentral/answers/99925-why-does-the-screensaver-get-captured-when-i-use-getframe-on-a-matlab-figure-window-while-creating-a



% Get CDATA from hardcopy using zbuffer
% Need to have PaperPositionMode be auto 
orig_mode = get(hfig, 'PaperPositionMode');
set(hfig, 'PaperPositionMode', 'auto');
cdata = hardcopy(hfig, '-Dzbuffer', '-r0');
% Restore figure to original state
set(hfig, 'PaperPositionMode', orig_mode); 
end