
; Csound template for a IanniX score receiving a cursor message with default value
; (i.e cursor_id, cursor_xPos, cursor_yPos).

<CsoundSynthesizer>
<CsOptions>
-o dac
</CsOptions>
<CsInstruments>
sr				=					44100
ksmps			=					10
nchnls			=					2
0dbfs			=					1

; the IanniX OSC out port
gihandle		OSCinit		57120

; Initialization of global variables that will be used mapping cursor_xPos and cursor_yPos
gkCursorX	init				0
gkCursorY	init				0

; Receiver instrument
; NOTE: in Csound all OSC variables need to be k-rate variables.
					instr			1

; the receive values must be initialized.
kcursor_id						init				0
kcursor_xPos					init				0
kcursor_yPos					init				0

; Listener loop
nxtmsg:
	kcurs		OSClisten	gihandle, "/cursor", "iff", kcursor_id, kcursor_xPos, kcursor_yPos

	if (kcurs == 0) kgoto ex
		gkCursorX		=			kcursor_xPos
		gkCursorY		=			kcursor_yPos

		kgoto				nxtmsg
ex:
					endin

; Template instrument that use the global variables set in instrument 1
					instr			10

; Here You can use gkCursorX, gkCursorY values
					printk2		gkCursorX
					printk2		gkCursorY

; Be careful of the values range!

					endin

</CsInstruments>
<CsScore>
; instr  start  dur
i1       0      65
i10      0      65
e
</CsScore>
</CsoundSynthesizer>
