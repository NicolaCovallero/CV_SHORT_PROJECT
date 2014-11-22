function [ lines ] = votingLines( lines_in )
%[ lines ] = votingLines( lines_in )
%   Consider more lines as making part of one bigger line when these lines
%   are near each other and share the same orientation. Short lines are
%   eliminated when do not belong to a bigger line 

    n = length(lines_in);
    
    lines_acc=lines(h);
    if (euc_distance( lines_in(h).point1 , lines_in(k).point1 ) < tol || ...
       euc_distance( lines_in(h).point1 , lines_in(k).point2 )) &
       (lines_in(h).theta - lines_in(k).theta) <= tol_theta
       
       lines_acc=[lines_in(k) lines_acc];
   
    elseif (euc_distance( lines_in(h).point2 , lines_in(k).point1 ) < tol || ...
       euc_distance( lines_in(h).point2 , lines_in(k).point2 )) &
       (lines_in(h).theta - lines_in(k).theta) <= tol_theta
       
       lines_acc=[lines_acc lines_in(k)];
   
    end    
        

end

function distance=euc_distance(A,B)
    distance=sqrt((A(1,1)-B(1,1))^2+(A(1,2)+B(1,2))^2);
end