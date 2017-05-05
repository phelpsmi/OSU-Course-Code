A2writeup.dvi: A2writeup.tex
	pdflatex A2writeup.tex

Paper1.ps: A2writeup.dvi
	dvips -Ppdf -G0 A2writeup.dvi
	# the -G0 fixes the ligature problem.

A2writeup.pdf: A2writeup.ps
	ps2pdf A2writeup.ps

PDF: A2writeup.pdf
	xpdf A2writeup.pdf

all: pdf

clean:
	rm -f *.pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

.PHONY: all show clean ps pdf showps
