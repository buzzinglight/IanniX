
; TO USE WITH: ChebyshevTest01.nxscore

<CsoundSynthesizer>
<CsOptions>
-o dac
</CsOptions>
<CsInstruments>
sr				=					44100
ksmps			=					10
nchnls			=					2
0dbfs			=					1

gihandle		OSCinit		57120

gk1				init				0
gk2				init				0
gk3				init				0
gk4				init				0
gk5				init				0
gk6				init				0

gaudio			init				0

					instr			1

kcursor_id						init				0
kcursor_xPos					init				0
kcursor_yPos					init				0
ifactor		=					0.025

nxtmsg:
	kcurs		OSClisten	gihandle, "/cursor", "iff", kcursor_id, kcursor_xPos, kcursor_yPos

	if (kcurs == 0) kgoto ex
	; ogni cursore si applica ad uno dei coefficienti del polinomio di Chebyshev (range -1/1)
	; X da 0 a 120 (sec.), Y da -100 a 100 (scalata a -1/+1)
	if (kcursor_id==11) then
		gk1		=		kcursor_yPos * ifactor

		elseif (kcursor_id==12) then
			gk2		=		kcursor_yPos * ifactor
		
		elseif (kcursor_id==13) then
			gk3		=		kcursor_yPos * ifactor
		
		elseif (kcursor_id==14) then
			gk4		=		kcursor_yPos * ifactor
		
		elseif (kcursor_id==15) then
			gk5		=		kcursor_yPos * ifactor
		
		elseif (kcursor_id==16) then
			gk6		=		kcursor_yPos * ifactor
		endif
		kgoto				nxtmsg
ex:
					endin

; time-varying mixture of first six harmonics
					instr			10

kamp				=					1
kcps				=					256
ax				oscili			kamp, kcps, 1

; waveshape it
ay				chebyshevpoly		ax, 0, gk1, gk2, gk3, gk4, gk5, gk6

iLev				=					p4
aenv				linseg			0.0, 0.05, iLev, p3 - 0.1, iLev, 0.05, 0.0
gaudio			=					gaudio + (ay*aenv)
					endin

					instr			100

; Compression
ithreshold	=					0.75
icomp1			=					0.752
icomp2			=					0.5
irtime			=					0.1
iftime			=					0.1

aOut				dam				gaudio, ithreshold, icomp1, icomp2, irtime, iftime
gaudio			=					0

; Reverb
iFxLevel		=					0.4
aL, aR			reverbsc		aOut, aOut, 0.7, 18000
aL				=					(aL*iFxLevel) + (aOut*(1-iFxLevel))
aR				=					(aR*iFxLevel) + (aOut*(1-iFxLevel))
					outs				aL, aR
					fout				"ChebyTest3.wav", 6, aL, aR
					endin

</CsInstruments>
<CsScore>
f1 0 32768 10 1

i1   0  130
i10  0  130  0.6
i100 0  136

e

</CsScore>
</CsoundSynthesizer>
