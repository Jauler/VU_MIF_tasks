SOURCE=paper


all: pdf


pdf: paper.tex
	pdflatex $(SOURCE).tex
	bibtex $(SOURCE).aux
	pdflatex $(SOURCE).tex


clean:
	rm $(SOURCE).aux
	rm $(SOURCE).dvi
	rm $(SOURCE).pdf
	rm $(SOURCE).log


