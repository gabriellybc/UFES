%
% Imprimir tabela X horizontal
% Input:
%	Variáveis X o seu nome, string de formatação e título da tabela
% 	Exemplo printTabX( X, 'X', '%5.2f', 'Tabela X-Y' )
%
function printTabX( X, Xname, formstr, titulo )
	fprintf('%s\n', titulo );
	maxlen = max(length(Xname));
	namestr = sprintf('%%%ds%%2s', maxlen+1 );
        
        maxlenX = 0;
        for i=1:length(X)
            maxlenX = max(maxlenX, length(sprintf(formstr, X(i))));
        end
	sep1 = repmat(['-'], 1, maxlen+3);
        sep = repmat(['-'], 1, maxlenX+2);

        fprintf( '%s', sep1 );
	for i=1:length(X)
		fprintf( '%s', sep );
	end
        fprintf( '\n' );
	fprintf( namestr, Xname, ' |' );
	for i=1:length(X)
                buf = sprintf(formstr, X(i));
                fmt = sprintf('%%%ds', maxlenX+2 );
		fprintf( fmt, buf );
	end
        fprintf( '\n%s', sep1 );
	for i=1:length(X)
		fprintf( '%s', sep );
	end
	fprintf('\n\n');
end


