A3writeup.dvi: A3writeup.tex
	pdflatex A3writeup.tex

A3writeup.ps: A3writeup.dvi
	dvips -Ppdf -G0 A3writeup.dvi
	# the -G0 fixes the ligature problem.

A3writeup.pdf: A3writeup.ps
	ps2pdf A3writeup.ps

PDF: A3writeup.pdf
	xpdf A3writeup.pdf

all: pdf

clean:
	rm -f *.pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

.PHONY: all show clean ps pdf showps
