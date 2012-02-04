
; TO USE WITH: CsoundTest03.nxscore

; Simple additive synthesis with amplitudes drived by the cursors y values; cursors x values
; are mapped to time.

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

gkValue		init				0

; Listener.
					instr			1

; the received values must be initialized
kcursor_id						init				0
kcursor_xPos					init				0
kcursor_yPos					init				0

nxtmsg:
	kcurs		OSClisten	gihandle, "/cursor", "iff", kcursor_id, kcursor_xPos, kcursor_yPos

	if (kcurs == 0) kgoto ex

		if (kcursor_id == 11) then
			gkValue1			=				kcursor_yPos*0.01
			;printk				1, gkValue

		elseif (kcursor_id == 12) then
			gkValue2			=				kcursor_yPos*0.01
			;printk				1, gkValue

		elseif (kcursor_id == 13) then
			gkValue3			=				kcursor_yPos*0.01
			;printk				1, gkValue

		elseif (kcursor_id == 14) then
			gkValue4			=				kcursor_yPos*0.01
			;printk				1, gkValue

		elseif (kcursor_id == 15) then
			gkValue5			=				kcursor_yPos*0.01
			;printk				1, gkValue

		elseif (kcursor_id == 16) then
			gkValue6			=				kcursor_yPos*0.01
			;printk				1, gkValue

		endif
		kgoto				nxtmsg
ex:
					endin

					instr			10

iBaseFreq	=					100

aOut1			poscil			gkValue1, iBaseFreq, 1
aOut2			poscil			gkValue2, iBaseFreq*1.5,  1
aOut3			poscil			gkValue3, iBaseFreq*2,  1
aOut4			poscil			gkValue4, iBaseFreq*2.9,  1
aOut5			poscil			gkValue5, iBaseFreq*3.5,  1
aOut6			poscil			gkValue6, iBaseFreq*4.1,  1

aOut				=					aOut1 + aOut2 + aOut3 + aOut4 + aOut5 + aOut6
aL, aR			pan2				aOut, 0.5
					outs				aL, aR
					fout				"CsoundTest03.wav", 6, aL, aR
					endin

</CsInstruments>
<CsScore>
f1 0 32768 10 1

i1  0 65
i10 0 65

e

</CsScore>
</CsoundSynthesizer>
