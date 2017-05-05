A4writeup.dvi: A4writeup.tex
	pdflatex A4writeup.tex

A4writeup.ps: A4writeup.dvi
	dvips -Ppdf -G0 A4writeup.dvi
	# the -G0 fixes the ligature problem.

A4writeup.pdf: A4writeup.ps
	ps2pdf A4writeup.ps

PDF: A4writeup.pdf
	xpdf A4writeup.pdf

all: pdf

clean:
	rm -f *.pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

.PHONY: all show clean ps pdf showps
