
; TO USE WITH: CsoundTest02.nxscore

; Simple additive synthesis with frequency drived by the cursors y values; cursors x values
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
			gkValue1			=				kcursor_yPos*10
			;printk				1, gkValue

		elseif (kcursor_id == 12) then
			gkValue2			=				kcursor_yPos*10
			;printk				1, gkValue

		elseif (kcursor_id == 13) then
			gkValue3			=				kcursor_yPos*10
			;printk				1, gkValue

		elseif (kcursor_id == 14) then
			gkValue4			=				kcursor_yPos*10
			;printk				1, gkValue

		elseif (kcursor_id == 15) then
			gkValue5			=				kcursor_yPos*10
			;printk				1, gkValue

		elseif (kcursor_id == 16) then
			gkValue6			=				kcursor_yPos*10
			;printk				1, gkValue

		endif
		kgoto				nxtmsg
ex:
					endin

					instr			10

aOut1			poscil			0.1, gkValue1, 1
aOut2			poscil			0.1, gkValue2, 1
aOut3			poscil			0.1, gkValue3, 1
aOut4			poscil			0.1, gkValue4, 1
aOut5			poscil			0.1, gkValue5, 1
aOut6			poscil			0.1, gkValue6, 1

aOut				=					aOut1 + aOut2 + aOut3 + aOut4 + aOut5 + aOut6
					outs				aOut, aOut
					fout				"CsoundTest02.wav", 6, aOut, aOut
					endin

</CsInstruments>
<CsScore>
f1 0 32768 10 1

i1  0 65
i10 0 65

e

</CsScore>
</CsoundSynthesizer>
