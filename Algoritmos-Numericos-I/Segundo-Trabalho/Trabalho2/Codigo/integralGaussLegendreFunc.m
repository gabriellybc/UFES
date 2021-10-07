% n = número de subdivisões
function IGL = integralGaussLegendreFunc( func, a, b, n, T, A, verbose )
	bma2 = (b-a)/2.0; bpa2 = (b+a)/2.0;
	IGL = zeros(1,length(bma2));
	for i=0:n
		ti = T(n+1,i+1);
		Ai = A(n+1,i+1);
		IGL = IGL + Ai * func(bma2*ti+bpa2);
	end
	IGL = IGL .* bma2;

    if ~verbose
      return;
    end
	% Explicitação didática
	if 1 && length(IGL)==1
	% Explicitação didática
	fprintf('I_GL%d = (b-a)/2[ ', n+1 );
	for i=0:n
		fprintf('A%d*f((b-a)/2*t%d+(a+b)/2)', i+1, i+1  ); if i==n fprintf(' ]\n'); else fprintf(' + '); end;
	end
	fprintf('       = (%.2f-%.2f)/2[ ', b, a );
	for i=0:n
		ti = T(n+1,i+1); Ai = A(n+1,i+1);
		fprintf('%f*f((%.2f-%.2f)/2*%f+(%.2f+%.2f)/2)', Ai, b, a, ti, b, a  ); if i==n fprintf(' ]\n'); else fprintf(' + '); end;
	end
	fprintf('       = %.4f[ ', bma2 );
	for i=0:n
		ti = T(n+1,i+1); Ai = A(n+1,i+1);
		fprintf('%f*f(%.3f*%f+%.3f)', Ai, bma2, ti, bpa2  ); if i==n fprintf(' ]\n' ); else fprintf(' + '); end;
	end
	fprintf('       = %.4f[ ', bma2 );
	for i=0:n
		ti = T(n+1,i+1); Ai = A(n+1,i+1); fti = func(bma2*ti+bpa2);
		fprintf('%f*%.4f', Ai, fti  ); if i==n fprintf(' ] = %.10f\n', IGL); else fprintf(' + '); end;
	end
	
	end
end




