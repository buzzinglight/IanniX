<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="fr_FR">
<context>
    <name>ExtKinectManager</name>
    <message>
        <location filename="../extkinectmanager.cpp" line="55"/>
        <source>IanniX</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../extkinectmanager.cpp" line="55"/>
        <source>Kinect</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>ExtMidiManager</name>
    <message>
        <location filename="../extmidimanager.cpp" line="188"/>
        <source>MIDI %1 on ch. %2, send note(%3)=%4</source>
        <translation>MIDI %1 sur ch. %2, note(%3)=%4</translation>
    </message>
    <message>
        <location filename="../extmidimanager.cpp" line="208"/>
        <source>MIDI %1 on ch. %2, send CC(%3)=%4</source>
        <translation>MIDI %1 sur ch. %2, CC (%3)=%4</translation>
    </message>
    <message>
        <location filename="../extmidimanager.cpp" line="226"/>
        <source>MIDI %1 on ch. %2, send PGM=%3</source>
        <translation>MIDI %1 sur ch. %2, PGM=%3</translation>
    </message>
    <message>
        <location filename="../extmidimanager.cpp" line="248"/>
        <source>MIDI %1 on ch. %2, send bend=%3</source>
        <translation>MIDI %1 sur ch. %2, bend=%3</translation>
    </message>
</context>
<context>
    <name>ExtOscPatternAsk</name>
    <message utf8="true">
        <location filename="../extoscpatternask.ui" line="14"/>
        <source>IanniX — Message editor</source>
        <translation>IanniX — Éditeur de messages</translation>
    </message>
    <message>
        <location filename="../extoscpatternask.ui" line="254"/>
        <source>ADD A NEW MESSAGE</source>
        <translation>AJOUTER UN NOUVEAU MESSAGE</translation>
    </message>
    <message>
        <location filename="../extoscpatternask.ui" line="270"/>
        <source>REMOVE CURRENT MESSAGE</source>
        <translation>SUPPRIMER LE MESSAGE</translation>
    </message>
    <message>
        <location filename="../extoscpatternask.cpp" line="43"/>
        <location filename="../extoscpatternask.cpp" line="111"/>
        <source>Message %1</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../extoscpatternask.h" line="56"/>
        <source>EN</source>
        <translation>FR</translation>
    </message>
</context>
<context>
    <name>ExtOscPatternEditor</name>
    <message>
        <location filename="../extoscpatterneditor.ui" line="20"/>
        <source>IanniX</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="230"/>
        <source>osc://ip_out:57120/cursor cursor_id cursor_value_x cursor_value_y cursor_xPos cursor_yPos cursor_zPos - Default OSC message for cursors</source>
        <translation>osc://ip_out:57120/cursor cursor_id cursor_value_x cursor_value_y cursor_xPos cursor_yPos cursor_zPos - Message OSC par défaut pour les curseurs</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="235"/>
        <source>midi://midi_out/note 0 69 127 5 - Play a MIDI note (A - 440Hz) during 5 seconds on channel #0</source>
        <translation>midi://midi_out/note 0 69 127 5 - Joue une note MIDI (LA - 440Hz) pendant 5 secondes sur le canal #0</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="240"/>
        <source>midi://midi_out/cc 1 0 cursor_value_y - Send a MIDI control change on controler #0 on channel #1 depending on cursor position</source>
        <translation>midi://midi_out/cc 1 0 cursor_value_y - Envoie un control change MIDI depuis le contrôleur #0 sur le canal #1, suivant la valeur du curseur</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="250"/>
        <source>direct:// setSpeedF 10 1 - Make the cursor #10 start (please set its Master Speed to 0 before)</source>
        <translation>direct:// setSpeedF 10 1 - Démarre le curseur #10 (il faut mettre au préalable la vitesse générale du curseur à 0)</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="290"/>
        <location filename="../extoscpatterneditor.ui" line="334"/>
        <source>Clear the message</source>
        <translation>Effacer le message</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="293"/>
        <location filename="../extoscpatterneditor.ui" line="337"/>
        <source>Click here to clear the message</source>
        <translation>Cliquer ici pour effacer le message</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="299"/>
        <location filename="../extoscpatterneditor.ui" line="798"/>
        <location filename="../extoscpatterneditor.ui" line="883"/>
        <location filename="../extoscpatterneditor.ui" line="968"/>
        <location filename="../extoscpatterneditor.ui" line="1053"/>
        <location filename="../extoscpatterneditor.ui" line="1138"/>
        <location filename="../extoscpatterneditor.ui" line="1223"/>
        <source>X</source>
        <translation>X</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="343"/>
        <source>learn</source>
        <translation>learn</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="376"/>
        <source>SEND THROUGH</source>
        <translation>ENVOYER SUR</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="207"/>
        <location filename="../extoscpatterneditor.ui" line="210"/>
        <location filename="../extoscpatterneditor.ui" line="398"/>
        <location filename="../extoscpatterneditor.ui" line="401"/>
        <source>Select here the protocol used to transmit message</source>
        <translation>Sélectionnez ici un protocole pour envoyer le messager</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="220"/>
        <source>Templates</source>
        <translation>Modèles</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="245"/>
        <source>direct:// goto 2 - Make score go back to timecode 000:02.000</source>
        <translation>direct:// goto 2 - Fait revenir le playback au timecode 000:02.000</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="225"/>
        <source>osc://ip_out:57120/trigger trigger_id trigger_xPos trigger_yPos trigger_zPos cursor_id - Default OSC message for triggers</source>
        <translation>osc://ip_out:57120/trigger trigger_id trigger_xPos trigger_yPos trigger_zPos cursor_id - Message OSC par défaut pour les triggers</translation>
    </message>
    <message>
        <source>osc://ip_out:57120/cursor cursor_id cursor_value_x cursor_value_y cursor_xPos cursor_yPos cursor_zPos - Default OSC message for curves</source>
        <translation type="obsolete">osc://ip_out:57120/cursor cursor_id cursor_value_x cursor_value_y cursor_xPos cursor_yPos cursor_zPos - Message OSC par défaut pour les curseurs</translation>
    </message>
    <message>
        <source>midi://midi_out/note 0 69 127 5 - Play a MIDI note (A - 440Hz) during 5 seconds</source>
        <translation type="obsolete">midi://midi_out/note 0 69 127 5 - Joue une note MIDI (LA - 440Hz) pendant 5 secondes</translation>
    </message>
    <message>
        <source>midi://midi_out/cc 0 20 cursor_value_y - Send a MIDI control change on controler #20 depending on cursor position</source>
        <translation type="obsolete">midi://midi_out/cc 0 20 cursor_value_y - Envoie un control change MIDI depuis le contrôleur #20, suivant la valeur du curseur</translation>
    </message>
    <message>
        <source>direct:// setSpeedF 10 1 - Make the cursor #10 start (please set its speedF parameter to 0 before)</source>
        <translation type="obsolete">direct:// setSpeedF 10 1 - Démarre le curseur #10 (il faut mettre au préalable le Master Speed du curseur à 0)</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="433"/>
        <source>TO HOST</source>
        <translation>VERS L&apos;HOTE</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="455"/>
        <location filename="../extoscpatterneditor.ui" line="458"/>
        <source>Select or type the destination application/host IP</source>
        <translation>Selectionner ou taper l&apos;application ou l&apos;IP destination</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="496"/>
        <source>ON PORT</source>
        <translation>SUR LE PORT</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="521"/>
        <location filename="../extoscpatterneditor.ui" line="524"/>
        <source>Select or type the destination application/host port number</source>
        <translation>Selectionner ou taper l&apos;application/numéro de port de destination</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="556"/>
        <source>TO ADDRESS</source>
        <translation>VERS L&apos;ADRESSE</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="578"/>
        <location filename="../extoscpatterneditor.ui" line="581"/>
        <source>Select or type an OSC address to reach</source>
        <translation>Selectionner ou taper l&apos;adresse OSC à atteindre</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="613"/>
        <source>TO MIDI DEVICE</source>
        <translation>VERS</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="635"/>
        <location filename="../extoscpatterneditor.ui" line="638"/>
        <source>Select or type a MIDI device to reach</source>
        <translation>Selectionner ou taper le périphérique MIDI à atteindre</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="676"/>
        <source>TO CONTROL</source>
        <translation>CONTRÔLE</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="701"/>
        <location filename="../extoscpatterneditor.ui" line="704"/>
        <source>Select here a MIDI control</source>
        <translation>Selectionner ici un contrôle MIDI</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="736"/>
        <source>VALUE 1</source>
        <translation>VALEUR 1</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="758"/>
        <location filename="../extoscpatterneditor.ui" line="761"/>
        <location filename="../extoscpatterneditor.ui" line="846"/>
        <location filename="../extoscpatterneditor.ui" line="849"/>
        <location filename="../extoscpatterneditor.ui" line="931"/>
        <location filename="../extoscpatterneditor.ui" line="934"/>
        <location filename="../extoscpatterneditor.ui" line="1016"/>
        <location filename="../extoscpatterneditor.ui" line="1019"/>
        <location filename="../extoscpatterneditor.ui" line="1101"/>
        <location filename="../extoscpatterneditor.ui" line="1104"/>
        <location filename="../extoscpatterneditor.ui" line="1186"/>
        <location filename="../extoscpatterneditor.ui" line="1189"/>
        <source>Type here a IanniX variable or your custom value</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="789"/>
        <location filename="../extoscpatterneditor.ui" line="877"/>
        <location filename="../extoscpatterneditor.ui" line="962"/>
        <location filename="../extoscpatterneditor.ui" line="1047"/>
        <location filename="../extoscpatterneditor.ui" line="1132"/>
        <location filename="../extoscpatterneditor.ui" line="1217"/>
        <source>Clear the value</source>
        <translation>Effacer la valeur</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="792"/>
        <location filename="../extoscpatterneditor.ui" line="880"/>
        <location filename="../extoscpatterneditor.ui" line="965"/>
        <location filename="../extoscpatterneditor.ui" line="1050"/>
        <location filename="../extoscpatterneditor.ui" line="1135"/>
        <location filename="../extoscpatterneditor.ui" line="1220"/>
        <source>Click here to clear the value</source>
        <translation>Cliquer ici pour effacer la valeur</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="824"/>
        <source>VALUE 2</source>
        <translation>VALEUR 2</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="909"/>
        <source>VALUE 3</source>
        <translation>VALEUR 3</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="994"/>
        <source>VALUE 4</source>
        <translation>VALEUR 4</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="1079"/>
        <source>VALUE 5</source>
        <translation>VALEUR 5</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.ui" line="1164"/>
        <source>VALUE 6</source>
        <translation>VALEUR 6</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="121"/>
        <location filename="../extoscpatterneditor.cpp" line="139"/>
        <source>VALUE %1</source>
        <translation>VALEUR %1</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="122"/>
        <source>QUERY ARG. %1</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="153"/>
        <source>MIDI CHANNEL</source>
        <translation>CANAL MIDI</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="155"/>
        <source>NOTE NUMBER</source>
        <translation>NUMÉRO NOTE</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="156"/>
        <source>VELOCITY</source>
        <translation>VELOCITÉ</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="157"/>
        <source>DURATION</source>
        <translation>DURÉE</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="161"/>
        <source>PROGRAM ID</source>
        <translation>ID PROGRAMME</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="165"/>
        <source>CONTROLLER ID</source>
        <translation>ID CONTRÔLLEUR</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="166"/>
        <location filename="../extoscpatterneditor.cpp" line="170"/>
        <source>VALUE</source>
        <translation>VALEUR</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="202"/>
        <source>COMMAND %1</source>
        <translation>COMMANDE %1</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="203"/>
        <source>XML NODE %1</source>
        <translation>NOEUD XML %1</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="304"/>
        <source>MIDI/OSC learn</source>
        <translation>Apprentissage MIDI/OSC</translation>
    </message>
    <message>
        <location filename="../extoscpatterneditor.cpp" line="304"/>
        <source>Please send an event to IanniX

Move a slider on your surface control or press a MIDI noteâ¦</source>
        <translation>Veuillez envoyer un événement à IanniX

Bougez un slider sur votre interface de contrôle ou appuyez sur une note MIDI</translation>
    </message>
</context>
<context>
    <name>ExtScriptManager</name>
    <message>
        <location filename="../extscriptmanager.h" line="87"/>
        <source>Filename conflict</source>
        <translation>Conflit de nom de fichiers</translation>
    </message>
    <message>
        <location filename="../extscriptmanager.h" line="87"/>
        <source>The file can&apos;t be renamed! A file with this name exists in your project.</source>
        <translation>Ce fichier ne peut pas être renommé ! Un fichier avec le même nom existe déjà dans votre projet.</translation>
    </message>
</context>
<context>
    <name>ExtScriptVariableAsk</name>
    <message>
        <location filename="../extscriptvariableask.ui" line="14"/>
        <source>IanniX</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../extscriptvariableask.ui" line="108"/>
        <source>PLEASE ENTER VALUES TO LAUNCH SCRIPT:</source>
        <translation>SAISIE DES VARIABLES DE SCRIPT :</translation>
    </message>
    <message>
        <location filename="../extscriptvariableask.ui" line="118"/>
        <source>List of script variables</source>
        <translation>Liste des variables de scripts</translation>
    </message>
    <message>
        <location filename="../extscriptvariableask.ui" line="121"/>
        <source>Double-click on a column to change a value</source>
        <translation>Double-cliquer sur une case pour changer sa valeur</translation>
    </message>
    <message>
        <location filename="../extscriptvariableask.ui" line="131"/>
        <source>VARIABLE</source>
        <translation>VARIABLE</translation>
    </message>
    <message>
        <location filename="../extscriptvariableask.ui" line="136"/>
        <source>VALUE</source>
        <translation>VALEUR</translation>
    </message>
</context>
<context>
    <name>ExtTcpManager</name>
    <message>
        <location filename="../exttcpmanager.cpp" line="62"/>
        <source>New TCP client connected</source>
        <translation>Nouveau clien TCP connecté</translation>
    </message>
</context>
<context>
    <name>IanniX</name>
    <message>
        <location filename="../iannix.cpp" line="357"/>
        <location filename="../iannix.cpp" line="360"/>
        <source>CURRENT PROJECT</source>
        <translation>PROJET COURANT</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="363"/>
        <source>TOOLS</source>
        <translation>OUTILS</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="366"/>
        <source>EXAMPLES</source>
        <translation>EXEMPLES</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="460"/>
        <source>SVG Import</source>
        <translation>Import SVG</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="460"/>
        <location filename="../iannix.cpp" line="490"/>
        <location filename="../iannix.cpp" line="501"/>
        <location filename="../iannix.cpp" line="531"/>
        <source>Coordinates systems are different.
Please enter a scale factor: </source>
        <translation>Les systèmes de coordonnées sont différents.
Merci de saisir un facteur de taille :</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="490"/>
        <location filename="../iannix.cpp" line="501"/>
        <source>Image import</source>
        <translation>Import d&apos;image</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="531"/>
        <source>Text import</source>
        <translation>Import de texte</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="773"/>
        <source>IanniX Update Center</source>
        <translation>Mises à jour de IanniX</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="773"/>
        <source>A new version of IanniX is available</source>
        <translation>Une nouvelle version de IanniX est disponible</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="773"/>
        <source>Would you like to update IanniX with the new version ?</source>
        <translation>Voulez-vous mettre à jour IanniX avec la nouvelle version ?</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="992"/>
        <source>New score</source>
        <translation>Nouvelle partition</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="992"/>
        <source>Enter the name of your new score:</source>
        <translation>Veuillez entrer un nom pour la nouvelle partition :</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1002"/>
        <location filename="../iannix.cpp" line="1020"/>
        <location filename="../iannix.cpp" line="1051"/>
        <location filename="../iannix.cpp" line="1153"/>
        <location filename="../iannix.cpp" line="1214"/>
        <location filename="../iannix.cpp" line="1227"/>
        <source>Filename conflict</source>
        <translation>Conflit de nom de fichiers</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1002"/>
        <location filename="../iannix.cpp" line="1020"/>
        <location filename="../iannix.cpp" line="1153"/>
        <location filename="../iannix.cpp" line="1214"/>
        <source>The file can&apos;t be created! A file with this name exists in your project.</source>
        <translation>Ce fichier ne peut pas être créé ! Un fichier avec le même nom existe déjà dans votre projet.</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1010"/>
        <source>New script</source>
        <translation>Nouveau script</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1010"/>
        <source>Enter the name of your new script:</source>
        <translation>Veuillez entrer un nom du nouveau script :</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1027"/>
        <source>Open IanniX Project Folder</source>
        <translation>Ouvrir un projet IanniX</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1044"/>
        <location filename="../iannix.cpp" line="1221"/>
        <source>File rename</source>
        <translation>Renommage de fichier</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1044"/>
        <location filename="../iannix.cpp" line="1221"/>
        <source>New name of script:</source>
        <translation>Nouveau nom du script :</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1051"/>
        <location filename="../iannix.cpp" line="1227"/>
        <source>The file can&apos;t be renamed! A file with this name exists in your project.</source>
        <translation>Ce fichier ne peut pas être renommé ! Un fichier avec le même nom existe déjà dans votre projet.</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1059"/>
        <location filename="../iannix.cpp" line="1233"/>
        <source>File remove</source>
        <translation>Suppression de fichier</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1059"/>
        <location filename="../iannix.cpp" line="1233"/>
        <source>The file will be removed from your disk. Are you sure?</source>
        <translation>Le fichier va être supprimé de votre disque. Êtes-vous sûr ?</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1067"/>
        <location filename="../iannix.cpp" line="1147"/>
        <location filename="../iannix.cpp" line="1208"/>
        <source>File duplication</source>
        <translation>Dupplication de fichier</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1067"/>
        <source>Enter the desired name of the duplicated score</source>
        <translation>Entrer le nom de la partition duppliquée</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1088"/>
        <location filename="../iannix.cpp" line="1090"/>
        <location filename="../iannix.cpp" line="1092"/>
        <location filename="../iannix.cpp" line="1113"/>
        <location filename="../iannix.cpp" line="1115"/>
        <location filename="../iannix.cpp" line="1117"/>
        <location filename="../iannix.cpp" line="2517"/>
        <source>IanniX</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1127"/>
        <source>Open a project</source>
        <translation>Ouvrir un projet</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1128"/>
        <location filename="../iannix.cpp" line="1181"/>
        <source>New</source>
        <translation>Nouveau</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1129"/>
        <location filename="../iannix.cpp" line="1182"/>
        <source>Duplicate</source>
        <translation>Dupliquer</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1130"/>
        <location filename="../iannix.cpp" line="1183"/>
        <source>Rename</source>
        <translation>Renommer</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1131"/>
        <location filename="../iannix.cpp" line="1184"/>
        <source>Remove</source>
        <translation>Supprimer</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1133"/>
        <location filename="../iannix.cpp" line="1186"/>
        <source>Click here to open a project folder</source>
        <translation>Cliquez ici pour ouvrir un projet</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1134"/>
        <source>Click here to create a new score</source>
        <translation>Cliquer ici pour créer une nouvelle partition</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1135"/>
        <source>Click here to duplicate the score to a new one</source>
        <translation>Cliquer ici pour dupliquer la partition</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1136"/>
        <source>Click here to rename the score</source>
        <translation>Cliquer ici pour renommer la partition</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1137"/>
        <source>Click here to remove the score from project folder</source>
        <translation>Cliquer ici pour supprimer la partition du projet</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1147"/>
        <location filename="../iannix.cpp" line="1208"/>
        <source>Name of duplicate script:</source>
        <translation>Nom du script duppliqué :</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1178"/>
        <source>Run</source>
        <translation>Exécuter</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1179"/>
        <source>Open</source>
        <translation>Ouvrir</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1180"/>
        <source>Open with default external editor</source>
        <translation>Ouvrir avec l&apos;éditeur par défaut</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1185"/>
        <source>Click here to run this script</source>
        <translation>Cliquer ici pour exécuter le script</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1187"/>
        <source>Click here to create a new script</source>
        <translation>Cliquer ici pour créer un nouveau script</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1188"/>
        <source>Click here to duplicate the script to a new one</source>
        <translation>Cliquer ifi pour dupliquer le script</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1189"/>
        <source>Click here to rename the script</source>
        <translation>Cliquer ici pour renommer le script</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1190"/>
        <source>Click here to remove the script from project folder</source>
        <translation>Cliquer icc pour supprimer le script du projet</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="1536"/>
        <source>Script:</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="2422"/>
        <source>has</source>
        <translation>a</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="2424"/>
        <source>s have</source>
        <translation>s ont</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="2425"/>
        <source>Score save</source>
        <translation>Enregistrer des partitions</translation>
    </message>
    <message>
        <location filename="../iannix.cpp" line="2425"/>
        <source>%1 document%2 been changed without saving.

Do you want to save modifications?</source>
        <translation>%1 document%2 été modifié(s) sans être sauvegardé(s).

Voulez-vous enregistrer les
modifications ?</translation>
    </message>
</context>
<context>
    <name>IanniXApp</name>
    <message>
        <location filename="../iannixapp.cpp" line="58"/>
        <source>Messages protocols</source>
        <translation>Protocoles</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="59"/>
        <source>OpenSoundControl message</source>
        <translation>Message OpenSoundControl</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="60"/>
        <source>Recursive/loopback message (sent directly to IanniX)</source>
        <translation>Message récursif/boucle locale (envoyé directement à IanniX)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="61"/>
        <source>MIDI message (control change, note on/off or program change)</source>
        <translation>Message MIDI (control change, note on/off ou program change)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="62"/>
        <source>Serial message (UART/RS232)</source>
        <translation>Message série (UART/RS232)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="63"/>
        <source>HTTP request to a webpage/webservice (GET)</source>
        <translation>Requête vers une page web/webservice (GET)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="64"/>
        <source>Raw UDP message (compatible with PureData)</source>
        <translation>Message en raw UDP (compatible avec PureData)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="65"/>
        <source>XML over TCP message (compatible with Flash/Director)</source>
        <translation>Message XML sur TCP (compatible avec Flash/Director)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="67"/>
        <source>Messages IP</source>
        <translation>Messages IP</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="68"/>
        <source>Destination is the default IP set in &quot;Network&quot; tab</source>
        <translation>IP par défaut (saisie dans l&apos;onglet &quot;Network&quot;)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="69"/>
        <source>Destination is your own computer</source>
        <translation>Cet ordinateur (IP locale)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="71"/>
        <source>Messages MIDI devices</source>
        <translation>Périphériques MIDI</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="72"/>
        <source>Destination is the default MIDI device set in &quot;Network&quot; tab</source>
        <translation>MIDI par défaut (saisi dans l&apos;onglet &quot;Network&quot;)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="73"/>
        <source>MIDI device created by IanniX (Mac &amp; Linux only)</source>
        <translation>Périphérique MIDI créé par IanniX (Mac &amp; Linux)</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="75"/>
        <source>Messages IP ports</source>
        <translation>Ports IP</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="76"/>
        <source>Default port used by IanniX</source>
        <translation>Port par défaut</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="77"/>
        <source>IanniX OSC default input</source>
        <translation>Port OSC entrant de IanniX</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="79"/>
        <source>Messages OSC addresses</source>
        <translation>Adresse OSC</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="80"/>
        <source>Default address used for triggers</source>
        <translation>Adresse par défaut des triggers</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="81"/>
        <source>Default address used for cursors</source>
        <translation>Adresse par défaut des curseurs</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="82"/>
        <source>Default address used for transport messages</source>
        <translation>Adresse par défaut du transport</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="83"/>
        <source>Default address used to reach IanniX</source>
        <translation>Adresse par défaut de IanniX</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="85"/>
        <source>Messages MIDI controls</source>
        <translation>Contrôles MIDI</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="86"/>
        <source>Send a control change</source>
        <translation>Envoi d&apos;un control change</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="87"/>
        <source>Send a bend</source>
        <translation>Envoi d&apos;un bend</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="88"/>
        <source>Send a program change</source>
        <translation>Envoi d&apos;un program change</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="89"/>
        <source>Send a note</source>
        <translation>Envoi d&apos;une note</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="91"/>
        <source>Messages values</source>
        <translation>Valeurs</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="92"/>
        <source>ID of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="93"/>
        <source>Group name of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="94"/>
        <source>Document name of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="95"/>
        <source>Label of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="96"/>
        <source>x coordinate of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="97"/>
        <source>y coordinate of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="98"/>
        <source>z coordinate of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="99"/>
        <source>x mapped coordinate of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="100"/>
        <source>y mapped coordinate of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="101"/>
        <source>z mapped coordinate of the triggered trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="102"/>
        <source>When trigger off-time is set, returns 127 when the trigger is trigged and 0 when the trigger is released</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="103"/>
        <source>Distance between the triggered trigger and the cursor that triggers the trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="104"/>
        <source>0 if trigger is triggered from left to right and 1 for the other side</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="105"/>
        <location filename="../iannixapp.cpp" line="132"/>
        <source>ID of the message (each message generates an ascending ID)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="106"/>
        <source>ID of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="107"/>
        <source>Group name of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="108"/>
        <source>Document name of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="109"/>
        <source>Label of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="111"/>
        <source>x coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="112"/>
        <source>y coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="113"/>
        <source>z coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="114"/>
        <source>x mapped coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="115"/>
        <source>y mapped coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="116"/>
        <source>z mapped coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="117"/>
        <source>Current progression of the cursor on the curve (in seconds)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="118"/>
        <source>Current progression of the cursor on the curve (in percentages, from 0.0 to 1.0)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="119"/>
        <source>Angle of the cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="121"/>
        <source>Variation of x coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="122"/>
        <source>Variation of y coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="123"/>
        <source>Variation of z coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="124"/>
        <source>Variation of x mapped coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="125"/>
        <source>Variation of y mapped coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="126"/>
        <source>Variation of z mapped coordinate of the running cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="127"/>
        <source>Variation of current progression of the cursor on the curve (in seconds)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="128"/>
        <source>Variation of current progression of the cursor on the curve (in percentages, from 0.0 to 1.0)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="129"/>
        <source>Variation of angle of the cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="131"/>
        <source>Number of loops done by the cursor on the curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="133"/>
        <source>ID of curve where the cursor runs on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="134"/>
        <source>Group name of curve where the cursor runs on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="135"/>
        <source>Document name of curve where the cursor runs on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="136"/>
        <source>Label of curve where the cursor runs on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="137"/>
        <source>x coordinate of curve where the cursor runs on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="138"/>
        <source>y coordinate of curve where the cursor runs on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="139"/>
        <source>z coordinate of curve where the cursor runs on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="140"/>
        <source>ID of the collided curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="141"/>
        <source>Group name of the collided curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="142"/>
        <source>Document name of the collided curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="143"/>
        <source>Label of the collided curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="144"/>
        <source>x coordinate of the collided curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="145"/>
        <source>y coordinate of the collided curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="146"/>
        <source>z coordinate of the collided curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="147"/>
        <source>x coordinate of the collision between the cursor and the curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="148"/>
        <source>y coordinate of the collision between the cursor and the curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="149"/>
        <source>x mapped coordinate of the collision between the cursor and the curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="150"/>
        <source>y mapped coordinate of the collision between the cursor and the curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="151"/>
        <source>Distance between the collision and the cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="152"/>
        <source>Set an OSC Timetag (compliant with Internet NTP timestamps) to message</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="153"/>
        <source>Playback status of score (&quot;play&quot;), &quot;stop&quot; or &quot;fastrewind&quot;)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="154"/>
        <source>Number of triggers in the current score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="155"/>
        <source>Number of cursors in the current score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="156"/>
        <source>Number of curves in the current score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="157"/>
        <source>Elapsed time in seconds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="158"/>
        <source>Elapsed time as displayed in Transport bar</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="160"/>
        <source>JavaScript useful functions</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="161"/>
        <source>Absolute value of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="162"/>
        <source>Arccosine of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="163"/>
        <source>Arcsine of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="164"/>
        <source>Arctangent of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="165"/>
        <source>Arctangent of x divided by y</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="166"/>
        <source>Next higher integer above x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="167"/>
        <source>Cosine of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="168"/>
        <source>e to the power x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="169"/>
        <source>Next lower integer below x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="170"/>
        <source>Logarithm to the base 2 of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="171"/>
        <source>Minimum of x and y</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="172"/>
        <source>Maximum of x and y</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="173"/>
        <source>x raised to the power y</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="174"/>
        <source>x rounded nearest integer, higher or lower</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="175"/>
        <source>Sine of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="176"/>
        <source>Square root of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="177"/>
        <source>x squared</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="178"/>
        <source>Tangent of x</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="179"/>
        <source>Radian angle x converted into degrees</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="180"/>
        <source>Degree angle x converted into radians</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="181"/>
        <source>Random number between low and high</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="182"/>
        <source>Values of x below min and above max are discarded</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="183"/>
        <source>Distance between the points (x1, y1, z1) and (x2, y2, z2)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="184"/>
        <source>Angle between the points (x1, y1) and (x2, y2)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="185"/>
        <source>Scale x to cover the range from low to high, assuming x ranges between 0.0 and 1.0:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="186"/>
        <source>Scale x to cover the range from low to high, assuming x ranges between 0.0 and 1.0, with mid being returned as the value for x=0.5</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="187"/>
        <source>Scale x to cover the range from low2 to high2, assuming x ranges between low1 and high1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="188"/>
        <source>Mathematical constant e</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="189"/>
        <source>Natural logarithm of 2</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="190"/>
        <source>Natural logarithm of 10</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="191"/>
        <source>Base 2 logarithm of e</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="192"/>
        <source>Logarithm to the base 10 of e</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="193"/>
        <source>Constant PI</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="194"/>
        <source>Two times PI</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="195"/>
        <source>PI over 3</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="196"/>
        <source>PI over 4</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="197"/>
        <source>PI over 2</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="198"/>
        <source>One over the square root of two</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="199"/>
        <source>Square root of two</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="201"/>
        <source>IanniX Commands</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="203"/>
        <source>Add an object</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="204"/>
        <source>Adds an object on the score. The keyword auto automatically assigns an ID to your object.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="205"/>
        <source>add &lt;trigger|curve|cursor&gt; &lt;id&gt;
add &lt;trigger|curve|cursor&gt; auto</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="211"/>
        <source>Remove an object</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="212"/>
        <source>Removes an object in the score thanks to its ID.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="213"/>
        <source>remove &lt;id&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="219"/>
        <source>Force object to send its message(s)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="220"/>
        <source>Forces an object to send its message(s).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="221"/>
        <source>trig &lt;target&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="227"/>
        <source>Erase a score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="228"/>
        <source>Erase all objects into the score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="229"/>
        <source>clear</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="235"/>
        <source>Defining a group</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="236"/>
        <source>Groups are identified by a word you are free to choose. Objects are not required to be part of a group.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="237"/>
        <source>setGroup &lt;target&gt; &lt;group name&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="243"/>
        <source>Enable/disable an object</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="244"/>
        <source>An object is enable by default, but you can disable it. Disabled objects will not send messages.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="245"/>
        <source>setActive &lt;target&gt; &lt;0|1&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="252"/>
        <source>Time before release (note off) of a trigger</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="253"/>
        <source>When a note is played thanks to a trigger, you can configure it to turn the note off automatically after a configurable delay. The time before release should normally be set to zero when note-off time is not being sent in the messages of this trigger.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="254"/>
        <source>setTriggerOff &lt;target&gt; &lt;delay&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="261"/>
        <source>Assign a cursor to a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="262"/>
        <source>After creating your cursor, make sure you have assigned the curve you want it to follow. You can use the keyword lastCurve to designate the last curve added.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="263"/>
        <source>setCurve &lt;cursor target&gt; &lt;curve target&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="269"/>
        <source>Width of the cursor play head</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="270"/>
        <source>You can edit in real time the width of a cursor in order to enable or disable triggers nearby.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="271"/>
        <source>setWidth &lt;target&gt; &lt;width&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="277"/>
        <source>Depth of the cursor play head</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="278"/>
        <source>You can edit in real time the depth of a cursor in order to enable or disable triggers nearby.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="279"/>
        <source>setDepth &lt;target&gt; &lt;depth&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="285"/>
        <source>Cursor loop pattern</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="286"/>
        <source>This parameter refers to the direction and the number of cycles. For example, with 1 1 0, the cursor will perform two cycles in the positive direction before stopping.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="287"/>
        <source>setPattern &lt;target&gt; &lt;easing&gt; 0 &lt;pattern&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="293"/>
        <source>Speed of a cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="294"/>
        <source>Cursors have a speed factor independent of each other. The travel time of a curve is also configurable. The cursor will evolve in the negative direction if the speed is negative, but time will continue to flow naturally.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="295"/>
        <source>setSpeed &lt;target&gt; auto &lt;duration&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="296"/>
        <source>setSpeed &lt;target&gt; &lt;speed factor&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="302"/>
        <source>Instantaneous speed of a cursor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="303"/>
        <source>Cursors have an instantaneous speed factor independent, very useful for real-time performances. As setSpeed, a negative speed is possible without affecting the global speed of the score.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="304"/>
        <source>setSpeedF &lt;target&gt; &lt;speed factor&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="310"/>
        <source>Cursor offsets</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="311"/>
        <source>You can choose to start your cursor at a certain point of the curve (marked in seconds) and limit it between certain values (also in seconds).
For example, the 2 4 6 offset means that your cursor will start your curve at the position t=2s then will travel to point t=6s to start again at the point t=4s.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="312"/>
        <source>setOffset &lt;target&gt; &lt;initial&gt; &lt;start&gt; &lt;end&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="318"/>
        <source>Instantaneous position (in seconds)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="319"/>
        <location filename="../iannixapp.cpp" line="327"/>
        <source>The position of a cursor can be modified in real time. This instruction does not work if you include it directly in your script, because at each execution, IanniX does a fastrewind.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="320"/>
        <source>setTime &lt;target&gt; &lt;time&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="326"/>
        <source>Instantaneous position (in percentages)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="328"/>
        <source>setTimePercent &lt;target&gt; &lt;time&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="334"/>
        <location filename="../iannixapp.cpp" line="343"/>
        <source>Mapping values</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="335"/>
        <location filename="../iannixapp.cpp" line="344"/>
        <source>You can set your cursor to send values within a chosen interval. For example, if it is operating in a 3x3 square, it can still send coordinates as values between 0 and 1.
Use setBoundsSource to indicate to IanniX the interval in which your cursor is located and setBoundsTarget to set the range of your sent values. Generally BoundsSource is correctly set by default.
You must use the variables cursor_value_x, cursor_value_y, trigger_value_x, trigger_value_y, collison_value_x or collison_value_y that values sent are those of boundsTarget.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="336"/>
        <location filename="../iannixapp.cpp" line="345"/>
        <source>setBoundsSource &lt;target&gt; &lt;x-top-left-corner&gt; &lt;y-top-left-corner&gt; &lt;x-bottom-right-corner&gt; &lt;y-bottom-right-corner&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="337"/>
        <location filename="../iannixapp.cpp" line="346"/>
        <source>setBoundsTarget &lt;target&gt; &lt;x-top-left-value&gt;  &lt;y-top-left-value&gt;  &lt;x-bottom-right-value&gt; &lt;y-bottom-right-value&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="353"/>
        <source>Shifting points of a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="354"/>
        <source>Shfit points from left to right or right to left</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="355"/>
        <source>shiftPoints &lt;target&gt; &lt;start point index&gt; &lt;-1|1&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="361"/>
        <source>Translating a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="362"/>
        <source>Translates a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="363"/>
        <source>translatePoints &lt;target&gt; &lt;dX&gt; &lt;dY&gt; &lt;dZ&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="369"/>
        <source>Translating a point of a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="370"/>
        <source>Translates a point of a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="371"/>
        <source>translatePoint &lt;target&gt; &lt;point index&gt; &lt;dX&gt; &lt;dY&gt; &lt;dZ&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="377"/>
        <source>Setting or modifying points of a curve (straight or Bezier)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="378"/>
        <location filename="../iannixapp.cpp" line="389"/>
        <source>A curve must be defined by a sequence of points. The points index starts at 0.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="379"/>
        <source>setPointAt &lt;target&gt; &lt;point index&gt; &lt;x&gt; &lt;y&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="380"/>
        <source>setPointAt &lt;target&gt; &lt;point index&gt; &lt;x&gt; &lt;y&gt; &lt;c1x&gt; &lt;c1y&gt; &lt;c2x&gt; &lt;c2y&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="381"/>
        <source>setPointAt &lt;target&gt; &lt;point index&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="382"/>
        <source>setPointAt &lt;target&gt; &lt;point index&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt; &lt;c1x&gt; &lt;c1y&gt; &lt;c1z&gt; &lt;c2x&gt; &lt;c2y&gt; &lt;c2z&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="388"/>
        <source>Setting or modifying points of a curve (with automatic smoothing)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="390"/>
        <source>setSmoothPointAt &lt;target&gt; &lt;point index&gt; &lt;x&gt; &lt;y&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="391"/>
        <source>setSmoothPointAt &lt;target&gt; &lt;point index&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="397"/>
        <source>Modifying x-coordinate of a point of a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="398"/>
        <location filename="../iannixapp.cpp" line="406"/>
        <location filename="../iannixapp.cpp" line="414"/>
        <location filename="../iannixapp.cpp" line="422"/>
        <source>Description</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="399"/>
        <source>setPointXAt &lt;target&gt; &lt;point index&gt; &lt;x&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="405"/>
        <source>Modifying y-coordinate of a point of a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="407"/>
        <source>setPointYAt &lt;target&gt; &lt;point index&gt; &lt;y&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="413"/>
        <source>Modifying z-coordinate of a point of a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="415"/>
        <source>setPointZAt &lt;target&gt; &lt;point index&gt; &lt;z&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="421"/>
        <source>Removing a point of a curve</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="423"/>
        <source>removePointAt &lt;point index&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="429"/>
        <source>Text curves</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="430"/>
        <source>A character can also be played like a curve.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="431"/>
        <source>setPointsTxt &lt;target&gt; &lt;scaling&gt; &lt;font&gt; &lt;text&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="437"/>
        <source>Manual SVG curve â cubic path</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="438"/>
        <source>A SVG curve is defined by a path that you can directly import from another software by copy / paste.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="439"/>
        <source>setPointsPath &lt;target&gt; &lt;scale&gt; &lt;svg path&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="445"/>
        <source>Manual SVG curve â polylines</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="446"/>
        <source>The SVG path of these curves is simply a set of points .</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="447"/>
        <source>setPointsLines &lt;target&gt; &lt;scale&gt; &lt;svg polyline&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="453"/>
        <source>Automatic vectorization</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="454"/>
        <source>A curve can be directly constructed from an image by an automatic vectorization.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="455"/>
        <source>setPointsImg &lt;target&gt; &lt;scaling&gt; &lt;filename&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="461"/>
        <source>Elliptical or circular curves</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="462"/>
        <source>Ellipses are defined by a major axis and a minor axis. To construct circles, the two axes must have the same value.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="463"/>
        <source>setPointsEllipse &lt;target&gt; &lt;width&gt; &lt;height&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="470"/>
        <source>Size of objects</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="471"/>
        <source>This function modifies the thickness of a curve or a cursor and the size of a trigger.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="472"/>
        <source>setSize &lt;target&gt; &lt;size&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="478"/>
        <source>Curve size (width/height)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="479"/>
        <location filename="../iannixapp.cpp" line="487"/>
        <source>The size of objects can be changed directly.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="480"/>
        <source>setResize &lt;target&gt; &lt;width&gt; &lt;height&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="486"/>
        <source>Curve size (scale factor)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="488"/>
        <source>setResizeF &lt;target&gt; &lt;scale factor&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="494"/>
        <source>Paths format</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="495"/>
        <source>Sets a style dotted with dash pattern which must be a sequence of 0 and 1, dash style defines the space between each dot.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="496"/>
        <source>setLine &lt;target&gt; &lt;dash style&gt; &lt;dash pattern&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="502"/>
        <source>Space position</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="503"/>
        <source>Sets an object on the score via the coordinates (x, y, z).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="504"/>
        <source>setPos &lt;target&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="510"/>
        <source>Adding text</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="511"/>
        <source>You can add a text description of your items on the score.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="512"/>
        <source>setLabel &lt;target&gt; &lt;label&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="520"/>
        <source>Assigning a message</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="521"/>
        <source>This command sets the message that an object must send (please refer to Messages Syntax help).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="522"/>
        <source>setMessage &lt;target&gt; &lt;period&gt;, &lt;message1&gt; &lt;variables&gt;, &lt;message2&gt;,message2, message3, â¦</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="528"/>
        <source>Send a message</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="529"/>
        <source>You can send manually a message (please refer to Messages Syntax help).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="530"/>
        <source>sendOsc &lt;message&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="537"/>
        <source>Solo/un-solo</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="538"/>
        <source>Solo/un-solo an object or a group (exactly like in Objects of inspector tab)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="539"/>
        <source>solo &lt;target&gt; &lt;0|1&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="546"/>
        <source>Mute/un-mute</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="547"/>
        <source>Mute/un-mute an object or a group (exactly like in Objects of inspector tab)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="548"/>
        <source>mute &lt;target&gt; &lt;1|0&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="555"/>
        <source>Creating a variable texture</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="556"/>
        <source>Save your texture as a variable. If you are using the following variables, the display is directly modified because native textures are saved under those variables. Use the tool &quot;restore triggers original shapes&quot; from the inspector &quot;scripts &amp; styles&quot; to find the original textures.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="557"/>
        <source>registerTexture &lt;variable&gt; &lt;x-top-left-corner&gt; &lt;y-top-left-corner&gt; &lt;x-bottom-right-corner&gt; &lt;y-bottom-right-corner&gt; &lt;file name&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="564"/>
        <source>Texture of an object</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="565"/>
        <location filename="../iannixapp.cpp" line="573"/>
        <location filename="../iannixapp.cpp" line="581"/>
        <location filename="../iannixapp.cpp" line="589"/>
        <location filename="../iannixapp.cpp" line="597"/>
        <source>Modify the texture of an object or a group with a preloaded texture (refer to registerTexture).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="566"/>
        <source>setTexture &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="572"/>
        <source>Texture of an active object that does not send any messages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="574"/>
        <source>setTextureActive &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="580"/>
        <source>Texture of an inactive object that does not send any messages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="582"/>
        <source>setTextureInactive &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="588"/>
        <source>Texture of an active object that send messages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="590"/>
        <source>setTextureActiveMessage &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="596"/>
        <source>Texture of an inactive object that send messages</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="598"/>
        <source>setTextureInactiveMessage &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="606"/>
        <source>Creating a variable color (RGB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="607"/>
        <location filename="../iannixapp.cpp" line="615"/>
        <source>IanniX can also save a color as a variable for reusing it more easily.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="608"/>
        <source>registerColor &lt;variable&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="614"/>
        <source>Creating a variable color (HSB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="616"/>
        <source>registerColor &lt;variable&gt; &lt;h&gt; &lt;s&gt; &lt;b&gt; &lt;a&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="622"/>
        <source>Color of an object (RGB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="623"/>
        <location filename="../iannixapp.cpp" line="632"/>
        <location filename="../iannixapp.cpp" line="642"/>
        <location filename="../iannixapp.cpp" line="651"/>
        <location filename="../iannixapp.cpp" line="660"/>
        <location filename="../iannixapp.cpp" line="669"/>
        <location filename="../iannixapp.cpp" line="679"/>
        <location filename="../iannixapp.cpp" line="688"/>
        <location filename="../iannixapp.cpp" line="697"/>
        <location filename="../iannixapp.cpp" line="706"/>
        <source>Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="624"/>
        <source>setColor &lt;target&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="625"/>
        <source>setColor &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="631"/>
        <source>Color of an object (HSB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="633"/>
        <source>setColorHue &lt;target&gt; &lt;h&gt; &lt;s&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="634"/>
        <source>setColorHue &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="641"/>
        <source>Color of an active object that does not send any messages (RGB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="643"/>
        <source>setColorActive &lt;target&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="644"/>
        <source>setColorActive &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="650"/>
        <source>Color of an inactive object that does not send any messages (RGB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="652"/>
        <source>setColorInactive &lt;target&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="653"/>
        <source>setColorInactive &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="659"/>
        <source>Color of an active object that send messages (RGB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="661"/>
        <source>setColorActiveMessage &lt;target&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="662"/>
        <source>setColorActiveMessage &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="668"/>
        <source>Color of an inactive object that send messages (RGB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="670"/>
        <source>setColorInactiveMessage &lt;target&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="671"/>
        <source>setColorInactiveMessage &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="678"/>
        <source>Color of an active object that does not send any messages (HSB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="680"/>
        <source>setColorActiveHue &lt;target&gt; &lt;h&gt; &lt;s&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="681"/>
        <source>setColorActiveHue &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="687"/>
        <location filename="../iannixapp.cpp" line="705"/>
        <source>Color of an inactive object that send messages (HSB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="689"/>
        <source>setColorInactiveHue &lt;target&gt; &lt;h&gt; &lt;s&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="690"/>
        <source>setColorInactiveHue &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="696"/>
        <source>Color of an inactive object that does not send any messages (HSB)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="698"/>
        <source>setColorActiveMessageHue &lt;target&gt; &lt;h&gt; &lt;s&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="699"/>
        <source>setColorActiveMessageHue &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="707"/>
        <source>setColorInactiveMessageHue &lt;target&gt; &lt;h&gt; &lt;s&gt; &lt;b&gt; &lt;a&gt;
</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="708"/>
        <source>setColorInactiveMessageHue &lt;target&gt; &lt;variable&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="716"/>
        <source>Resizing objects regardless of zoom</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="717"/>
        <source>Enabled by default, can automatically increase or decrease the size of the triggers and cursors when you zoom in / out the score in order to facilitate reading. Only the visual aspect is affected, the actual size of the objects is not changed.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="718"/>
        <source>autoSize &lt;0|1&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="724"/>
        <source>Zoom in score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="725"/>
        <source>Adjust the zoom using the script. The factor is in percent. e.g. A factor of 200 doubles the size of the display area.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="726"/>
        <source>zoom &lt;zoom factor&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="732"/>
        <source>Center score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="733"/>
        <source>Placing the point (x,y) in the center of the workspace</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="734"/>
        <source>center &lt;x&gt; &lt;y&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="740"/>
        <location filename="../iannixapp.cpp" line="741"/>
        <source>Resize the viewport</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="742"/>
        <source>viewport &lt;width&gt; &lt;height&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="749"/>
        <source>Export as an image snapshot</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="750"/>
        <source>Make a snapshot of current score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="751"/>
        <source>snapshot &lt;scale&gt; &lt;filename,optional&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="757"/>
        <location filename="../iannixapp.cpp" line="765"/>
        <source>Rotate score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="758"/>
        <location filename="../iannixapp.cpp" line="766"/>
        <source>Rotate the view about the x, y and z axes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="759"/>
        <location filename="../iannixapp.cpp" line="767"/>
        <source>rotate &lt;x-axis&gt; &lt;y-axis&gt; &lt;z-axis&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="773"/>
        <source>Playing the score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="774"/>
        <source>Enabling the playback</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="775"/>
        <source>play &lt;score speed&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="781"/>
        <source>Stopping the score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="782"/>
        <source>Disabling the playback</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="783"/>
        <source>stop</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="789"/>
        <source>Fastrewinding the score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="790"/>
        <source>Go back to the begging of score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="791"/>
        <source>fastrewind</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="797"/>
        <source>Speed of the score</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="798"/>
        <source>You can set the global speed of the score. A negative speed will evolve over time in the negative direction.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="799"/>
        <source>speed &lt;speed&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="805"/>
        <source>Load a score or a script</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="806"/>
        <source>Load a score or a script of the current project folder</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="807"/>
        <source>load &lt;score name&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="813"/>
        <source>Log information to console</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="814"/>
        <source>Log information to IanniX console (network tab)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="815"/>
        <source>log &lt;text&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="821"/>
        <source>Go to a specific timecode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="822"/>
        <source>Go to a specific timecode in seconds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="823"/>
        <source>goto &lt;time in seconds&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="829"/>
        <source>Control mouse</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="830"/>
        <source>Enable to move cursor of the mouse</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="831"/>
        <source>mouse &lt;x&gt; &lt;y&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="839"/>
        <source>Get IanniX window title</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="840"/>
        <source>Returns IanniX window title (scripts only)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="841"/>
        <source>title</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="847"/>
        <source>Make IanniX script sleeping (scripts only)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="848"/>
        <source>Set a sleep time. BE CAREFUL, IanniX will not respond during sleeping</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="849"/>
        <source>sleep &lt;duration&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="862"/>
        <location filename="../iannixapp.cpp" line="886"/>
        <location filename="../iannixapp.cpp" line="960"/>
        <location filename="../iannixapp.cpp" line="1002"/>
        <location filename="../iannixapp.cpp" line="1042"/>
        <location filename="../iannixapp.cpp" line="1072"/>
        <location filename="../iannixapp.cpp" line="1081"/>
        <source>EN</source>
        <translation>FR</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="868"/>
        <source>Introduction</source>
        <translation>Introduction</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="868"/>
        <source>Main&lt;br/&gt;elements</source>
        <translation>Éléments&lt;br/&gt;principaux</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="868"/>
        <source>Scripts</source>
        <translation>Scripts</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="868"/>
        <source>Reference</source>
        <translation>Référence</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="890"/>
        <source>Documentation</source>
        <translation>Documentation</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="891"/>
        <source>IanniX commands must specify a target at each execution:</source>
        <translation>Les commandes IanniX doivent spécifier une cible à chaque exécution :</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="892"/>
        <source>&lt;li&gt;&lt;code class=&apos;target&apos;&gt;id&lt;/code&gt; refers to a specific object.&lt;br/&gt;Example: &lt;span class=&apos;api&apos;&gt;&lt;code&gt;remove &lt;span class= &apos;target&apos;&gt;2&lt;/span&gt;&lt;/code&gt;&lt;/span&gt;&lt;/li&gt;&lt;li&gt;&lt;code class=&apos;target&apos;&gt;group_id&lt;/code&gt; refers to the entire group that can be a word.&lt;br/&gt;Example: &lt;span class=&apos;api&apos;&gt;&lt;code&gt;remove &lt;span class= &apos;target&apos;&gt;toto&lt;/span&gt;&lt;/code&gt;&lt;/span&gt;&lt;/li&gt;&lt;li&gt;&lt;code class=&apos;target&apos;&gt;all&lt;/code&gt; refers to all objects.&lt;br/&gt;Example: &lt;span class=&apos;api&apos;&gt;&lt;code&gt;remove &lt;span class= &apos;target&apos;&gt;all&lt;/span&gt;&lt;/code&gt;&lt;/span&gt;&lt;/li&gt;&lt;li&gt;&lt;code class=&apos;target&apos;&gt;current&lt;/code&gt; refers to the last created object.&lt;br/&gt;Example: &lt;span class=&apos;api&apos;&gt;&lt;code&gt;remove &lt;span class= &apos;target&apos;&gt;current&lt;/span&gt;&lt;/code&gt;&lt;/span&gt;&lt;/li&gt;</source>
        <translation>&lt;li&gt;&lt;code class=&apos;target&apos;&gt;id&lt;/code&gt; désigne un objet précis.&lt;br/&gt;Exemple : &lt;span class=&apos;api&apos;&gt;&lt;code&gt;remove &lt;span class=&apos;target&apos;&gt;2&lt;/span&gt;&lt;/code&gt;&lt;/span&gt;&lt;/li&gt; &lt;li&gt;&lt;code class=&apos;target&apos;&gt;group_id&lt;/code&gt; désigne le groupe entier qui peut être un mot.&lt;br /&gt; Exemple : &lt;span class=&apos;api&apos;&gt;&lt;code&gt;remove &lt;span class=&apos;target&apos;&gt;toto&lt;/span&gt;&lt;/code&gt;&lt;/span&gt;&lt;/li&gt;&lt;li&gt;&lt;code class=&apos;target&apos;&gt;all&lt;/code&gt; désigne tous les objets.&lt;br /&gt; Exemple : &lt;span class=&apos;api&apos;&gt;&lt;code&gt;remove &lt;span class=&apos;target&apos;&gt;all&lt;/span&gt;&lt;/code&gt;&lt;/span&gt;&lt;/li&gt; &lt;li&gt;&lt;code class=&apos;target&apos;&gt;current&lt;/code&gt; désigne le dernier objet créé.&lt;br /&gt; Exemple : &lt;span class=&apos;api&apos;&gt;&lt;code&gt;remove &lt;span class=&apos;target&apos;&gt;current&lt;/span&gt;&lt;/code&gt;&lt;/span&gt;&lt;/li&gt;</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="906"/>
        <source>Example:</source>
        <translation>Exemple :</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="915"/>
        <source>Copy / paste this example in IanniX to understand how the code works!</source>
        <translation>Copier/coller cet exemple dans IanniX pour voir son fonctionnement !</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="964"/>
        <source>Welcome and thank you for downloading IanniX!</source>
        <translation>Bienvenue et merci d&apos;avoir téléchargé IanniX !</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="965"/>
        <source>IanniX is a graphical open-source sequencer, based on Iannis Xenakis works, for digital art. IanniX syncs via Open Sound Control (OSC) events and curves to your real-time environment (PureData, C-Sound, SuperCollider, openFramework, Processing, vvvv, Live, Max/MSP/Jitterâ¦ and many others from our &lt;a href=&apos;http://www.iannix.org/EN/links.php&apos; target=&apos;_blank&apos;&gt;links&lt;/a&gt; section)!</source>
        <translation>IanniX est un séquenceur graphique open-source, inspiré des travaux de Iannis Xenakis, destiné à la création numérique. IanniX synchronise via Open Sound Control (OSC) des événements et courbes vers votre environnement temps-réel (PureData, C-Sound, SuperCollider, openFramework, Processing, vvvv, Live, Max/MSP/Jitter… et beaucoup d’autres dans notre section &lt;a href=&apos;http://www.iannix.org/en/links.php&apos; target=&apos;_blank&apos;&gt;links&lt;/a&gt; section) !</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="966"/>
        <source>Feel free to suscribe to our &lt;a href=&apos;http://iannix.org/EN/community.php&apos; target=&apos;_blank&apos;&gt;forum&lt;/a&gt;. Post your problems or tips to make live our community!</source>
        <translation>N’hésitez pas à vous inscrire sur notre &lt;a href=&apos;http://iannix.org/en/community.php&apos; target=&apos;_blank&apos;&gt;forum&lt;/a&gt;. Poster vos problèmes ou astuces pour faire vivre notre communauté !</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1013"/>
        <source>Installation</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1014"/>
        <source>IanniX is compatible with Linux, Mac OS X 10.6+ and Windows and does not require any particular installation.&lt;br/&gt;For Linux users of IanniX who do not build from source, we have included a compiled version that you can run by launching the file &lt;code&gt;IanniX.sh&lt;/code&gt;.</source>
        <translation>IanniX est compatible avec Linux, Mac OS X 10.6+ et Windows et ne nécessite pas d’installation particulière.&lt;br /&gt; Pour les utilisateurs de IanniX sous Linux qui ne souhaitent pas compiler depuis les sources, nous avons inclus une version compilée que vous pourrez exécuter en lançant le fichier &lt;code&gt;IanniX.sh&lt;/code&gt;.</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1015"/>
        <source>Open Sound Control</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1016"/>
        <source>Open Sound Control is a communication protocol that operates over the IP network (i.e. Ethernet, Wi-Fi, Internet). It is recognized by all operating systems and requires no drivers or network configuration. Some knowledge of networking is needed to more advanced uses.&lt;br /&gt; &lt;br /&gt; The golden rule about OSC is to match IP addresses and ports: a message sent by IanniX to &lt;code&gt;127.0.0.1:57120&lt;/code&gt; means that it is sent to the local machine on port &amp;nbsp;57120. The software that has to receive this message will have to open port 57120.</source>
        <translation>L’Open Sound Control est un protocole de communication qui fonctionne sur le réseau IP (donc sur Ethernet, Wi-Fi, sur Internet…). Il est reconnu par tous les systèmes d’exploitation et ne nécessite pas de drivers ou de configuration réseau. Quelques connaissances en réseau sont toutefois nécessaires pour des usages plus poussés.&lt;br/&gt;&lt;br/&gt; La règle d&apos;or pour l&apos;OSC est de faire correspondre les adresses IP et les ports : un message envoyé par IanniX au &lt;code&gt;127.0.0.1:57120&lt;/code&gt; signifie qu&apos;il est envoyé à la machine local sur le port&amp;nbsp;57120. L&apos;application qui veut recevoir ce message devra donc ouvrir le port 57120.</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1017"/>
        <source>MIDI</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1018"/>
        <source>In order to remain compatible with the MIDI stations, we have integrated the MIDI protocol natively.&lt;br/&gt; For Windows users who do not have MIDI hardware devices, you must install a virtual MIDI device such as &lt;a href=&apos;http://www.nerds.de/data/setuploopbe1.exe&apos;&gt;LoopBe&lt;/a&gt;.</source>
        <translation>Afin de rester compatible avec les stations MIDI, nous avons intégré nativement le protocole MIDI.&lt;br /&gt; Pour les utilisateurs de Windows qui ne possèdent pas de périphériques MIDI matériels, vous devez installer un périphérique MIDI virtuel tel que &lt;a href=&apos;http://www.nerds.de/data/setuploopbe1.exe&apos;&gt;LoopBe&lt;/a&gt;.</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1019"/>
        <source>Software &amp;amp; interfaces</source>
        <translation>Interfaces &amp;amp; logiciels</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1020"/>
        <source>We have made available patches/interfaces for commonly used software that we have tested. Click on &apos;Open Patches Folder&apos; from the IanniX toolbar to discover them.&lt;br/&gt; This is very simple examples that illustrate the principle of communication between IanniX and other software; we invite you to modify them and get inspired for your projects.</source>
        <translation>Nous avons mis à votre disposition des patches/interfaces pour les logiciels couramment utilisés que nous avons testés. Cliquez sur le bouton &apos;Open Patches Folder&apos; de la barre d&apos;outils depuis IanniX pour les découvrir.&lt;br/&gt; Il s&apos;agit d&apos;exemples très simples qui illustrent le principe de communication entre IanniX et les logiciels ; nous vous invitons à les modifier et à vous en inspirer pour vos projets.</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1021"/>
        <source>Bugs</source>
        <translation>Bugs</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1022"/>
        <source>IanniX is still on beta-testing, some bugs are still present but most features can be used properly. You can report errors in the &apos;Bugs&apos; section of our &lt;a href=&apos;http://iannix.org/EN/community.php&apos;&gt;forum&lt;/a&gt;.</source>
        <translation>IanniX est toujours en beta-testing, quelques bugs sont donc encore présents mais la plupart des fonctionnalités peuvent être employées correctement. Vous pouvez signaler les erreurs dans la section « Bugs » de notre &lt;a href=&apos;http://iannix.org/fr/community.php&apos;&gt;forum&lt;/a&gt;.</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1023"/>
        <source>Version tracking</source>
        <translation>Suivi de versions</translation>
    </message>
    <message>
        <source>Known bugs</source>
        <translation type="obsolete">Bugs connus</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1046"/>
        <source>Objects</source>
        <translation>Objets</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1047"/>
        <source>A IanniX score is composed of three main elements:</source>
        <translation>Une partition IanniX se compose de trois objets fondamentaux&amp;nbsp;:</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1048"/>
        <source>&lt;li&gt;&lt;b&gt;a trigger&lt;/b&gt; is a momentary event set in space; it is activated when &lt;b&gt;a cursor&lt;/b&gt; goes past it;&lt;/li&gt;&lt;li&gt;&lt;b&gt;a curve&lt;/b&gt; is a series of points set in space; it defines a trajectory&amp;nbsp;;&lt;/li&gt;&lt;li&gt;&lt;b&gt;a cursor&lt;/b&gt; is similar to a tape head. It triggers discrete events (&lt;b&gt;triggers&lt;/b&gt;) or continuous (values). It can follow &lt;b&gt;a curve&lt;/b&gt; or be completely free (controlled by the mouse, a graphic tablet or by another software).&lt;/li&gt;</source>
        <translation>&lt;li&gt;&lt;b&gt;un trigger&lt;/b&gt; est un événement ponctuel positionné dans l&apos;espace ; il est déclenché lors du passage d&apos;&lt;b&gt;un curseur&lt;/b&gt;&amp;nbsp;;&lt;/li&gt;&lt;li&gt;&lt;b&gt;une courbe&lt;/b&gt; est une suite de points dans l&apos;espace ; elle définit une trajectoire&amp;nbsp;;&lt;/li&gt;&lt;li&gt;&lt;b&gt;un curseur&lt;/b&gt; est une tête de lecture. Il déclenche des événements discrets (&lt;b&gt;triggers&lt;/b&gt;) ou continus (valeurs). Il peut suivre &lt;b&gt;une courbe&lt;/b&gt; ou être complètement libre (contrôlé par la souris, une tablette ou par un autre logiciel).&lt;/li&gt;</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1049"/>
        <source>Add objects</source>
        <translation>Ajouter des objets</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1050"/>
        <source>To set an object in space, you have three methods:</source>
        <translation>Pour positionner un objet dans l&apos;espace, vous disposez de trois méthodes :</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1051"/>
        <source>&lt;li&gt;&lt;b&gt;the graphic interface&lt;/b&gt; thanks to the toolbar;&lt;/li&gt;&lt;li&gt;&lt;b&gt;software interfaces&lt;/b&gt; controlling IanniX via Open Sound Control for example, through &lt;a href=&apos;reference.html&apos;&gt;IanniX commands&lt;/a&gt;;&lt;/li&gt;&lt;li&gt;&lt;b&gt;scripts&lt;/b&gt; that create generative scores via &lt;a href=&apos;script.html&apos;&gt;scripted commands&lt;/a&gt;.&lt;/li&gt;</source>
        <translation>&lt;li&gt;&lt;b&gt;l&apos;interface graphique&lt;/b&gt; à l&apos;aide de la &lt;a href=&apos;overview.html&apos;&gt;barre d&apos;outils&lt;/a&gt;&amp;nbsp;;&lt;/li&gt;&lt;li&gt;&lt;b&gt;les interfaces logicielles&lt;/b&gt; contrôlant IanniX en Open Sound Control par exemple, grâce au système de &lt;a href=&apos;reference.html&apos;&gt;commandes IanniX&lt;/a&gt;&amp;nbsp;;&lt;/li&gt;&lt;li&gt;&lt;b&gt;les scripts&lt;/b&gt; qui créé des partitions génératives via &lt;a href=&apos;script.html&apos;&gt;des commandes scriptées&lt;/a&gt;.&lt;/li&gt;</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1052"/>
        <source>Basic vocabulary</source>
        <translation>Vocabulaire fondamental</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1053"/>
        <source>A few simple concepts will enable you to understand the mechanisms of IanniX:</source>
        <translation>Quelques notions très simples vous permettront de comprendre les mécanismes de IanniX :</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1054"/>
        <source>&lt;li&gt;&lt;b&gt;the identifier (ID)&lt;/b&gt;: each object (trigger, curve or cursor) has an unique identifier;&lt;/li&gt;&lt;li&gt;&lt;b&gt;the group&lt;/b&gt;: objects can be grouped under a group name, allowing control of multiple objects at once.&lt;/li&gt;</source>
        <translation>&lt;li&gt;&lt;b&gt;l&apos;identifiant (ID)&lt;/b&gt; : chaque objet (trigger, courbe ou curseur) possède un identifiant unique&amp;nbsp;;&lt;/li&gt;&lt;li&gt;&lt;b&gt;le groupe&lt;/b&gt; : les objets peuvent être regroupés sous un nom de groupe, permettant le contrôle de plusieurs objets d&apos;un coup.&lt;/li&gt;</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1055"/>
        <source>Messages</source>
        <translation>Messages</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1056"/>
        <source>Message handling is the main function of IanniX. They can be sent by &lt;b&gt;cursors&lt;/b&gt; and &lt;b&gt;triggers&lt;/b&gt;.</source>
        <translation>La gestion des messages est la fonction principale de IanniX. Ils peuvent être envoyés par &lt;b&gt;les curseurs&lt;/b&gt; et &lt;b&gt;les triggers&lt;/b&gt;.</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1057"/>
        <source>To see if the messages are actually sent or received, IanniX displays a trace in the &apos;Messages&apos; section of inspector.</source>
        <translation>Pour savoir si les messages sont effectivement reçus ou envoyés, IanniX en affiche une trace dans la section « Messages » de l&apos;inspecteur.</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1058"/>
        <source>&lt;b&gt;Triggers&lt;/b&gt; usually send one only message when a cursor goes past them. IanniX is limited to sending one message per millisecond maximum.&lt;br/&gt;</source>
        <translation>&lt;b&gt;Les triggers&lt;/b&gt; n&apos;envoient généralement qu&apos;un seul message au passage du curseur et IanniX limite l&apos;envoi à 1 message par milliseconde maximum.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1059"/>
        <source>&lt;b&gt;Cursors&lt;/b&gt;, by default, generate messages every 20&amp;nbsp;ms (but you can change this time).</source>
        <translation>&lt;b&gt;Les curseurs&lt;/b&gt; génèrent par défaut des messages toutes les 20&amp;nbsp;ms (mais vous pouvez modifier cette période).</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1060"/>
        <source>To edit the message that a element has to send, click on &apos;Edit&apos; in the inspector after having selected the object or double-click on the object itself to display this window:</source>
        <translation>Pour éditer le message qu&apos;un objet doit envoyer, cliquez sur &apos;Edit&apos; dans l&apos;inspecteur après avoir sélectionné l’objet ou double-cliquez sur l’objet lui-même pour faire apparaître la fenêtre:</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1061"/>
        <source>Recursion</source>
        <translation>Récursivité</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1062"/>
        <source>IanniX can be controlled by IanniX itself (!). You can use all the protocols described above, but we recommend using OSC to communicate between two IanniX applications on network computers and use the &lt;code&gt;direct&lt;/code&gt; command to send messages inside one IanniX application.&lt;br/&gt;&lt;br /&gt;&lt;span class=&apos;titre&apos;&gt;Example:&amp;nbsp;&lt;/span&gt;</source>
        <translation>IanniX peut être contrôlé par IanniX lui-même (!). Vous pouvez utiliser tous les protocoles décrits précédemment mais nous vous recommandons d&apos;utiliser l&apos;OSC pour communiquer entre deux IanniX sur des ordinateurs en réseau et d&apos;utiliser la commande &lt;code&gt;direct&lt;/code&gt; pour envoyer des messages à l&apos;intérieur même de IanniX.&lt;br/&gt;&lt;br /&gt;&lt;span class=&apos;titre&apos;&gt;Exemple :&amp;nbsp;&lt;/span&gt;</translation>
    </message>
    <message>
        <location filename="../iannixapp.cpp" line="1063"/>
        <source>Copy / paste this example in Iannix to understand how the code works!</source>
        <translation>Copier/coller cet exemple dans IanniX pour voir son fonctionnement !</translation>
    </message>
</context>
<context>
    <name>NxGroup</name>
    <message>
        <location filename="../nxgroup.h" line="96"/>
        <source>Group</source>
        <translation>Groupe</translation>
    </message>
</context>
<context>
    <name>UiAbout</name>
    <message>
        <location filename="../uiabout.ui" line="26"/>
        <source>About IanniX</source>
        <translation>À propos de IanniX</translation>
    </message>
    <message utf8="true">
        <location filename="../uiabout.ui" line="86"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Arial&apos;; font-weight:400; font-style:normal;&quot;&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;IDEATION&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Thierry Coduys&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Adrien Lefevre&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Gerard Pape (CCMIX)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;CONTRIBUTORS&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Christopher Graham&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;WEB &amp;amp; IDENTITY&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Matthieu Ranc&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;IANNIX DEVELOPERS &lt;/span&gt;&lt;span style=&quot; font-weight:600; font-style:italic;&quot;&gt;(FORMER VERSIONS)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Adrien Lefevre &lt;span style=&quot; font-style:italic;&quot;&gt;(v0.54)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Guillaume Ferry &lt;span style=&quot; font-style:italic;&quot;&gt;(v0.6xx)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Pierre Jullian de la Fuente &amp;amp; Cyrill Duneau &lt;span style=&quot; font-style:italic;&quot;&gt;(v0.6xx)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Matthieu Ranc &amp;amp; Guillaume Jacquemin &lt;span style=&quot; font-style:italic;&quot;&gt;(v0.66)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;TESTERS &amp;amp; EXTERNAL CONTRIBUTORS&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Jean Bresson (OpenMusic)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Paul Crabbe (SuperCollider)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Francesco (C-Sound)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Cyrille Henry&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Thomas Thiery (PureData)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Romain Vuillet&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;THANKS TO&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Etienne Mathé (documentation), Joachim Montessuis and all users for their observations and suggestions and AFIM (Association Française d&apos;Informatique Musicale).&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Visit &lt;a href=&quot;http://www.iannix.org&quot;&gt;&lt;span style=&quot; text-decoration: underline; color:#000000;&quot;&gt;http://www.iannix.org&lt;/span&gt;&lt;/a&gt; for more information !&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Arial&apos;; font-weight:400; font-style:normal;&quot;&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;IDÉATION&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Thierry Coduys&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Adrien Lefevre&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Gerard Pape (CCMIX)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;CONTRIBUTEURS&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Christopher Graham&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;WEB &amp;amp; IDENTITÉ&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Matthieu Ranc&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;DÉVELOPPEURS IANNIX &lt;/span&gt;&lt;span style=&quot; font-weight:600; font-style:italic;&quot;&gt;(ANCIENNES VERSIONS)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Adrien Lefevre &lt;span style=&quot; font-style:italic;&quot;&gt;(v0.54)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Guillaume Ferry &lt;span style=&quot; font-style:italic;&quot;&gt;(v0.6xx)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Pierre Jullian de la Fuente &amp;amp; Cyrill Duneau &lt;span style=&quot; font-style:italic;&quot;&gt;(v0.6xx)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Matthieu Ranc &amp;amp; Guillaume Jacquemin &lt;span style=&quot; font-style:italic;&quot;&gt;(v0.66)&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;TESTEURS &amp;amp; CONTRIBUTEURS EXTERNES&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Jean Bresson (OpenMusic)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Paul Crabbe (SuperCollider)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Francesco (C-Sound)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Cyrille Henry&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Thomas Thiery (PureData)&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Romain Vuillet&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;MERCI À&lt;/span&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Etienne Mathé (documentation), Joachim Montessuis et tous les utilisateurs pour leur observations et suggestions et l&apos;AFIM (Association Française d&apos;Informatique Musicale).&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p align=&quot;center&quot; style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Visitez &lt;a href=&quot;http://www.iannix.org&quot;&gt;&lt;span style=&quot; text-decoration: underline; color:#000000;&quot;&gt;http://www.iannix.org&lt;/span&gt;&lt;/a&gt; pour plus d&apos;informations !&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../uiabout.ui" line="134"/>
        <location filename="../uiabout.cpp" line="26"/>
        <source>version</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiabout.ui" line="156"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Arial&apos;; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;PROJECT MANAGER&lt;/span&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Thierry Coduys&lt;/p&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;DEVELOPPEMENT&lt;/span&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Guillaume Jacquemin&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Arial&apos;; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;CHEF DE PROJET&lt;/span&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Thierry Coduys&lt;/p&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600;&quot;&gt;DÉVELOPPEMENT&lt;/span&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Guillaume Jacquemin&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../uiabout.cpp" line="26"/>
        <source>beta</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>UiEditor</name>
    <message utf8="true">
        <location filename="../uieditor.ui" line="14"/>
        <source>IanniX — Script Editor</source>
        <translation>IanniX — Éditeur de scripts</translation>
    </message>
    <message>
        <location filename="../uieditor.ui" line="41"/>
        <location filename="../uieditor.cpp" line="84"/>
        <source>IanniX</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uieditor.ui" line="55"/>
        <source>Save</source>
        <translation>Sauvegarder</translation>
    </message>
    <message>
        <location filename="../uieditor.ui" line="58"/>
        <source>Ctrl+S</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uieditor.ui" line="63"/>
        <source>Close</source>
        <translation>Fermer</translation>
    </message>
    <message>
        <location filename="../uieditor.ui" line="66"/>
        <source>Ctrl+W</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uieditor.cpp" line="84"/>
        <source>Script Editor</source>
        <translation>Éditeur de scripts</translation>
    </message>
</context>
<context>
    <name>UiHelp</name>
    <message>
        <location filename="../uihelp.ui" line="14"/>
        <source>IanniX Helper</source>
        <translation>Aide de IanniX</translation>
    </message>
    <message>
        <location filename="../uihelp.cpp" line="65"/>
        <source>SYNTAX</source>
        <translation>SYNTAXE</translation>
    </message>
    <message>
        <location filename="../uihelp.cpp" line="65"/>
        <location filename="../uihelp.cpp" line="67"/>
        <location filename="../uihelp.cpp" line="69"/>
        <source>IMPLEMENT IN SCRIPT</source>
        <translation>IMPLÉMENTER DANS LE SCRIPT</translation>
    </message>
    <message>
        <location filename="../uihelp.cpp" line="67"/>
        <source>EXAMPLE</source>
        <translation>EXEMPLE</translation>
    </message>
    <message>
        <location filename="../uihelp.cpp" line="69"/>
        <source>SNIPPET</source>
        <translation>SNIPPET</translation>
    </message>
</context>
<context>
    <name>UiInspector</name>
    <message utf8="true">
        <location filename="../uiinspector.ui" line="14"/>
        <source>IanniX — Inspector</source>
        <translation>IanniX — Inspecteur</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="279"/>
        <source>FILES</source>
        <translation>FICHIERS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="301"/>
        <source>SCORES</source>
        <translation>PARTITIONS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="314"/>
        <source>Scores list</source>
        <translation>Liste des partitions</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="317"/>
        <source>List of available scores (from your project folder and from IanniX folders). Double-click to open a score. Right-click to show contextual menu.</source>
        <translation>List de toutes les partitions (depuis le projet et depuis les dossiers IanniX). Double-cliquer pour ouvrir une partition. Clic-droit pour afficher le menu contextuel.</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="342"/>
        <source>SCRIPTS &amp; STYLES</source>
        <translation>SCRIPTS &amp;&amp; FEUILLES DE STYLE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="355"/>
        <source>Scripts list</source>
        <translation>Liste des scripts</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="358"/>
        <source>List of available scripts (from your project folder and from IanniX folders). Double-click to launch a script. Right-click to show contextual menu.</source>
        <translation>Liste de tous les scripts (depuis le projet et depuis les dossiers IanniX). Double-cliquer pour exécuter un script. Clic-droit pour afficher le menu contextuel.</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="388"/>
        <source>INFOS</source>
        <translation>INFOS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="409"/>
        <location filename="../uiinspector.cpp" line="556"/>
        <source>TRIGGER</source>
        <translation>TRIGGER</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="436"/>
        <source>ID / GROUP ID</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="464"/>
        <source>POSITION
(X / Y / Z)</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="493"/>
        <location filename="../uiinspector.ui" line="527"/>
        <location filename="../uiinspector.ui" line="561"/>
        <source>Change here the absolute coordinates of selected objects</source>
        <translation>Modifier ici les coordonnées absolues des objets sélectionnés</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="595"/>
        <source>SIZE
(W / H)</source>
        <translation>TAILLE
(L / H)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="624"/>
        <location filename="../uiinspector.ui" line="658"/>
        <source>Change here the size of selected objects</source>
        <translation>Modifier ici la taille des objets sélectionnés</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="692"/>
        <source>CURSOR
WIDTH / DEPTH</source>
        <translation>TAILLE (L / P)
DU CURSEUR</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="721"/>
        <source>Change here the cursor width</source>
        <translation>Modifier ici la taille du curseur</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="752"/>
        <source>CURSOR
LOOP PATTERN</source>
        <translation>RÉPÉTITION DU
CURSEUR</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="781"/>
        <source>CURSOR
OFFSETS</source>
        <translation>OFFSETS DES
CURSEURS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="814"/>
        <source>BEGINS FROM</source>
        <translation>DÉBUTE À</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="833"/>
        <source>Change here the initial offset (first iteration of a cursor on a curve). Positive initial offset means that cursor will start from a position on the curve whereas negative initial offset means that cursor start will be delayed.</source>
        <translation>Modifier ici l&apos;offset initial (première itération du curseur sur la courbe). Un offset initial positif signifie que le curseur démarre sur la courbe à une position données ; un offset initial négatif signifie que le curseur démarre avec un retard.</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="893"/>
        <source>GOES FROM</source>
        <translation>ÉVOLUE DE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="915"/>
        <source>Change here the start offset of a cursor defining the loop start point on a curve</source>
        <translation>Modifier ici l&apos;offset de démarrage définissant le point de départ d&apos;une boucle sur la courbe</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="943"/>
        <location filename="../uiinspector.ui" line="3019"/>
        <source>TO</source>
        <translation>À</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="965"/>
        <source>Change here the start offset of a cursor defining the loop end point on a curve</source>
        <translation>Modifier ici l&apos;offset de fin définissant le point de fin de boucle sur la courbe</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="968"/>
        <source>the end</source>
        <translation>la fin</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1019"/>
        <source>CURSOR SPEED
or LENGTH</source>
        <translation>VITESSE DU CURVEUR</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1050"/>
        <source>Change here the cursor speed factor (1.00 = nominal speed)</source>
        <translation>Modifier ici la vitesse du curseur (1.00 = vitesse nominale)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1091"/>
        <source>Change here the cursor run duration on the curve</source>
        <translation>Modifier ici la durée d&apos;une itération du curseur sur la courbe</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1140"/>
        <source>CURSOR
MASTER SPEED</source>
        <translation>VITESSE GÉNÉRALE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1169"/>
        <source>Change here the cursor master speed factor (1.00 = nominal speed) (total speed = master speed x speed)</source>
        <translation>Modifier ici la vitesse générale du curseur (1.00 = vitesse nominale) (vitesse total = vitesse générale x vitesse du curseur)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1203"/>
        <source>VALUE
MAPPING</source>
        <translation>MAPPING DE
VALEURS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1245"/>
        <source>x RANGE</source>
        <translation>x ÉVOLUE DE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1264"/>
        <location filename="../uiinspector.ui" line="1320"/>
        <location filename="../uiinspector.ui" line="1373"/>
        <location filename="../uiinspector.ui" line="1429"/>
        <location filename="../uiinspector.ui" line="1482"/>
        <location filename="../uiinspector.ui" line="1538"/>
        <location filename="../uiinspector.ui" line="1591"/>
        <location filename="../uiinspector.ui" line="1647"/>
        <location filename="../uiinspector.ui" line="1763"/>
        <location filename="../uiinspector.ui" line="1797"/>
        <location filename="../uiinspector.ui" line="1831"/>
        <location filename="../uiinspector.ui" line="1865"/>
        <source>Change here the values for the graphical mapping of cursors position</source>
        <translation>Modifier ici les valeurs pour le mapping des les coordonnées graphiques</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1298"/>
        <location filename="../uiinspector.ui" line="1407"/>
        <location filename="../uiinspector.ui" line="1516"/>
        <location filename="../uiinspector.ui" line="1625"/>
        <location filename="../uiinspector.ui" line="1899"/>
        <location filename="../uiinspector.ui" line="1921"/>
        <source>=&gt;</source>
        <translation>À</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1354"/>
        <location filename="../uiinspector.ui" line="1572"/>
        <location filename="../uiinspector.ui" line="1744"/>
        <source>MAPPED RANGE</source>
        <translation>=&gt; VALEURS DE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1463"/>
        <source>y RANGE</source>
        <translation>y ÉVOLUE DE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1681"/>
        <source>z RANGE</source>
        <translation>z ÉVOLUE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1935"/>
        <source>NO ITEMS SELECTED</source>
        <translation>AUCUN ÉLÉMENT SÉLECTIONNÉ</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1954"/>
        <source>Click here to change the group ID of the object</source>
        <translation>Cliquer ici pout modifier le group ID de l&apos;objet</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1960"/>
        <source>GROUP</source>
        <translation>GROUPE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="1979"/>
        <source>TRIGGER
OFF-TIME</source>
        <translation>TEMPS DE
RELÂCHE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2008"/>
        <source>Change here the duration of a MIDI note</source>
        <translation>Modifier ici la durée d&apos;une note MIDI</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2039"/>
        <source>LABEL</source>
        <translation>ÉTIQUETTE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2055"/>
        <source>Type here a label for selected objects</source>
        <translation>Taper ici l&apos;étiquette pour les objets sélectionnés</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2077"/>
        <source>ACTIVE</source>
        <translation>ACTIF</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2093"/>
        <source>Click here to enable/disable the object on the score</source>
        <translation>Cliquer ici pour activer/désactiver l&apos;objet dans la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2115"/>
        <source>Click here to edit the message send by the selected objects</source>
        <translation>Cliquer ici pour éditer le(s) message(s) envoyé(s) par les objets sélectionnés</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2121"/>
        <source>EDIT</source>
        <translation>ÉDITER</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2140"/>
        <source>MESSAGES</source>
        <translation>MESSAGES</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2168"/>
        <source>COLORS</source>
        <translation>COULEURS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2204"/>
        <source>Change here the color of objects that are ACTIVE and that DOESN&apos;T SEND messages</source>
        <translation>Modifier ici la couleur des objets ACTIFS qui N&apos;ENVOIENT PAS de messages</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2226"/>
        <source>Change here the color of objects that are INACTIVE and that DOESN&apos;T SEND messages</source>
        <translation>Modifier ici la couleur des objets INACTIFS qui N&apos;ENVOIENT PAS de messages</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2248"/>
        <source>Change here the color of objects that are ACTIVE and that SEND messages</source>
        <translation>Modifier ici la couleur des objets ACTIFS qui ENVOIENT des messages</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2270"/>
        <source>Change here the color of objects that are INACTIVE and that SEND messages</source>
        <translation>Modifier ici la couleur des objets INACTIFS qui ENVOIENT de messages</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2304"/>
        <source>THICKNESS</source>
        <translation>ÉPAISSEUR</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2332"/>
        <source>Change here the tickness of selected objects</source>
        <translation>Modofier ici l&apos;épaisseur des objets sélectionnés</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2366"/>
        <source>Change here the periodicity of emitted messages</source>
        <translation>Modifier ici la périodicité des messages envoyés</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2388"/>
        <source>SENT EACH</source>
        <translation>ENVOYÉ CHAQUE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2413"/>
        <source>Click here to change the unique ID of the object</source>
        <translation>Cliquer ici pour modifier l&apos;ID unique de l&apos;objet</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2419"/>
        <location filename="../uiinspector.ui" line="2788"/>
        <source>ID</source>
        <translation>ID</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2441"/>
        <source>Select here the cursor acceleration on a curve</source>
        <translation>Sélectionner ici le courbe d&apos;accélération du curseur du la courbe</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2460"/>
        <source>Change here the cursor depth</source>
        <translation>Modifier ici la profondeur du curseur</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2491"/>
        <source>CURVE
POINTS</source>
        <translation>POINTS DE
LA COURBE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2508"/>
        <source>Type here the points coordinates (x, y, z) and the Bezier control points (c1x, c1y, c1z, c2x, c2y, c2z). Checkboxes allow you to activate automatic smoothing or not.</source>
        <translation>Taper ici les coordonnées des points (x, y, z) et les points de contrôle de Bézier (c1x, c1y, c1z, c2x, c2y, c2z). Les cases à cocher permette d&apos;activer un lissage automatique de la courbe.</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2521"/>
        <source>Index</source>
        <translation>Numéro</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2526"/>
        <source>x</source>
        <translation>x</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2531"/>
        <source>y</source>
        <translation>y</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2536"/>
        <source>z</source>
        <translation>z</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2541"/>
        <source>Smooth</source>
        <translation>Lissage</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2546"/>
        <source>c1x</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2551"/>
        <source>c1y</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2556"/>
        <source>c1z</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2561"/>
        <source>c2x</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2566"/>
        <source>c2y</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2571"/>
        <source>c2z</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2594"/>
        <source>Type here the speed pattern separated by spaces</source>
        <translation>Taper ici des vitesses de curseurs séparées par des espaces</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2601"/>
        <source>1 0 - One run on curve</source>
        <translation>1 0 - Une seule itération sur la courbe</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2606"/>
        <source>1 - Loop on curve</source>
        <translation>1 - Boucle sur la courbe</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2611"/>
        <source>1 -1 0 - Single roundtrip on curve </source>
        <translation>1 -1 0 - Aller/retour sur la courbe</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2616"/>
        <source>1 -1 - Loop roundtrip on curve </source>
        <translation>1 -1 - Aller/retour sur la courbe en boucle</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2621"/>
        <source>1 2 0 - One normal run, another at double speed</source>
        <translation>1 2 0 - Une itération normale, puis une autre à vitesse double</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2658"/>
        <location filename="../uiinspector.ui" line="2741"/>
        <source>OBJECTS</source>
        <translation>OBJETS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2669"/>
        <source>Display/hide triggers</source>
        <translation>Afficher/cacher les triggers</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2672"/>
        <source>Click here to show/hide triggers of the current score</source>
        <translation>Cliquer ici pour afficher/cacher les triggers de la partition courante</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2678"/>
        <location filename="../uiinspector.cpp" line="413"/>
        <location filename="../uiinspector.cpp" line="558"/>
        <source>TRIGGERS</source>
        <translation>TRIGGERS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2688"/>
        <source>Display/hide cursors</source>
        <translation>Afficher/cacher les curseurs</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2691"/>
        <source>Click here to show/hide cursors of the current score</source>
        <translation>Cliquer ici pour afficher/cacher les curseurs de la partition courante</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2697"/>
        <location filename="../uiinspector.cpp" line="414"/>
        <location filename="../uiinspector.cpp" line="566"/>
        <source>CURSORS</source>
        <translation>CURSEURS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2707"/>
        <source>Display/hide curves</source>
        <translation>Afficher/cacher les courbes</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2710"/>
        <source>Click here to show/hide curves of the current score</source>
        <translation>Cliquer ici pour afficher/cacher les courbes de la partition courante</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2716"/>
        <location filename="../uiinspector.cpp" line="415"/>
        <location filename="../uiinspector.cpp" line="562"/>
        <source>CURVES</source>
        <translation>COURBES</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2751"/>
        <source>List of objects</source>
        <translation>Liste des objets</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2754"/>
        <source>Click on a row to highlight and select object in score. Click on checkboxes to switch on/off and solo objects of the current score</source>
        <translation>Cliquer sur une ligne pour sélectionner un objet de la partition. Cocher les cases pour activer/désactiver ou mettre en solo un objet de la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2773"/>
        <source>TYPE</source>
        <translation>TYPE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2778"/>
        <location filename="../uiinspector.ui" line="2897"/>
        <source>ON/OFF</source>
        <translation>ON/OFF</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2783"/>
        <location filename="../uiinspector.ui" line="2902"/>
        <source>S</source>
        <translation>S</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2793"/>
        <source>GROUP ID</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2818"/>
        <location filename="../uiinspector.ui" line="2824"/>
        <source>Switch on all objects</source>
        <translation>Active tous les objets</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2821"/>
        <source>Click here to switch on all objects of the current score</source>
        <translation>Cliquer ici pour activer tous les objets de la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2843"/>
        <location filename="../uiinspector.ui" line="2849"/>
        <source>Disable solo for all objects</source>
        <translation>Désactiver le solo pour les objets</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2846"/>
        <source>Click here to disable solo of all objects of the current score</source>
        <translation>Cliquer ici pour désactiver le solo de tous les objets de la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2868"/>
        <location filename="../uiinspector.ui" line="2907"/>
        <location filename="../uiinspector.cpp" line="422"/>
        <source>GROUPS</source>
        <translation>GROUPES</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2878"/>
        <source>List of objects group name</source>
        <translation>Liste des groupes</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2881"/>
        <source>Click on a row to highlight and select groups in score. Click on checkboxes to switch on/off and solo groups of the current score</source>
        <translation>Cliquer sur une ligne pour sélectionner un groupe de la partition. Cocher les cases pour activer/désactiver ou mettre en solo un groupe de la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2932"/>
        <location filename="../uiinspector.ui" line="2938"/>
        <source>Switch on all groups</source>
        <translation>Active tous les groupes</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2935"/>
        <source>Click here to switch on of all objects of the current score</source>
        <translation>Cliquer ici pour désactiver tous les objets de la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2957"/>
        <location filename="../uiinspector.ui" line="2963"/>
        <source>Disable solo for all groups</source>
        <translation>Désactiver le solo pour les groupes</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2960"/>
        <source>Click here to disable solo of all groups of the current score</source>
        <translation>Cliquer ici pour désactiver le solo de tous les groups de la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2984"/>
        <source>Z-RANGE FROM</source>
        <translation>AFFICHAGE DES Z DE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2994"/>
        <location filename="../uiinspector.ui" line="3026"/>
        <source>Z-range values</source>
        <translation>Borne des Z à afficher</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="2997"/>
        <source>Change here the minimum displayable Z-value. Objects with a lower Z values will not be displayed.</source>
        <translation>Modificer ici le Z minimum à afficher. Les objets avec un Z inférieur ne seront pas visibles.</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3029"/>
        <source>Change here the maximum displayable Z-value. Objects with a higher Z values will not be displayed.</source>
        <translation>Modificer ici le Z maximum à afficher. Les objets avec un Z supérieurs ne seront pas visibles.</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3055"/>
        <source>CAMERA FOLLOWS OBJECT ID</source>
        <translation>CAMÉRA SUIT L&apos;OBJET</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3077"/>
        <source>Camera Follow ID</source>
        <translation>ID l&apos;objet à suivre avec la caméra</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3080"/>
        <source>Type here the ID of the object that the camera will follow</source>
        <translation>Taper ici l&apos;ID de l&apos;objet à suivre avec la caméra</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3083"/>
        <source>no objects</source>
        <translation>pas d&apos;objets</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3114"/>
        <source>Light off unused curves</source>
        <translation>Atténue les courbes non utilisées</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3117"/>
        <source>Click here to light on/off curves on which no cursor are running</source>
        <translation>Cliquer ici estomper les courbes non parcourues par un curseur</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3123"/>
        <source>LIGHT OFF UNUSED CURVES</source>
        <translation>ESTOMPER LES COURBES NON UTILISÉES</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3138"/>
        <source>NETWORK</source>
        <translation>RÉSEAU</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3160"/>
        <source>SENT MESSAGES</source>
        <translation>MESSAGES ENVOYÉS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3176"/>
        <source>Sent messages</source>
        <translation>Messages envoyés</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3179"/>
        <source>Logs all the sent messages (will slow down IanniX if kept on-screen)</source>
        <translation>Affiche les messages envoyés (ralentit IanniX si affiché en permanence)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3205"/>
        <source>RECEIVED MESSAGES</source>
        <translation>MESSAGES REÇUS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3221"/>
        <source>Received messages</source>
        <translation>Messages reçus</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3224"/>
        <source>Logs all the received messages (will slow down IanniX if kept on-screen)</source>
        <translation>Affiche les messages reçus (ralentit IanniX si affiché en permanence)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3252"/>
        <source>NETWORK CONFIGURATION</source>
        <translation>CONFIGURATION RÉSEAU</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3279"/>
        <source>OSC IN PORT</source>
        <translation>PORT OSC IN</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3298"/>
        <source>OSC in port</source>
        <translation>Port entrant OSC</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3301"/>
        <source>Type here the OSC in port number</source>
        <translation>Taper ici le numéro du port entrant OSC</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3329"/>
        <source>RAW UDP IN PORT</source>
        <translation>PORT RAW UDP IN</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3354"/>
        <source>TRANSPORT
MESSAGE</source>
        <translation>MESSAGE DE
TRANSPORT</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3374"/>
        <source>Raw UDP in port</source>
        <translation>Port entrant UDP brut</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3377"/>
        <source>Type here the raw UDP in port number</source>
        <translation>Taper ici le numéro du port entrant raw UDP</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3402"/>
        <source>SYNC
MESSAGE</source>
        <translation>MESSAGE DE
SYCHRONISATION</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3416"/>
        <source>Sync message</source>
        <translation>Message de synchronisation</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3419"/>
        <source>Type here the message that will be sent when clicking on &quot;Sync&quot;</source>
        <translation>Taper ici le message à envoyer pour la synchronisation</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3444"/>
        <source>MAKE OSC
BUNDLE ON</source>
        <translation>BUNDLE OSC
POUR L&apos;IP/PORT</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3470"/>
        <source>OSC bundle address</source>
        <translation>Adresse du bundle OSC</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3473"/>
        <source>Type here the IP address number associated to bundled messages. All OSC messages using this IP/port will be bundled.</source>
        <translation>Taper ici l&apos;adresse IP sortante des messages OSC à mettre en bundles.</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3495"/>
        <source>OSC bundle port</source>
        <translation>Port du bundle OSC</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3498"/>
        <source>Type here the port number associated to bundled messages. All OSC messages using this IP/port will be bundled.</source>
        <translation>Taper ici le numéro du port sortant des messages OSC à mettre en bundles.</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3523"/>
        <source>HTTP IN PORT</source>
        <translation>PORT HTTP IN</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3542"/>
        <source>HTTP in port</source>
        <translation>Port entrant HTTP</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3545"/>
        <source>Type here the HTTP in port number</source>
        <translation>Taper ici le numéro du port entrant HTTP</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3558"/>
        <source>Transport message</source>
        <translation>Message de transport</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3561"/>
        <source>Type here the message that will be sent when playback status changed (play, pause, fast rewind)</source>
        <translation>Taper ici le message à envoyer quand le playback change d&apos;état (play, pause, retour à zéro)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3586"/>
        <source>TCP/XML
SERVER IN PORT</source>
        <translation>PORT TCP/XML
SERVER IN</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3606"/>
        <source>TCP/XML Server in port</source>
        <translation>Port entrant du serveur TCP/XML</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3609"/>
        <source>Type here the TCP/XML Server in port number</source>
        <translation>Tape ici le port entrant du serveur TCP/XML</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3647"/>
        <source>DEFAULT IP
(ALIAS IP_OUT)</source>
        <translation>IP PAR DÉFAUT
(ALIAS IP_OUT)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3661"/>
        <source>Default IP address</source>
        <translation>Adresse IP par défaut</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3664"/>
        <source>Type here the default IP address used by messages containing the keyword ip_out</source>
        <translation>Taper ici l&apos;adresse IP par défaut utilisée pour les messages contenant le mot-clef ip_out</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3692"/>
        <source>DEFAULT MIDI OUT
(ALIAS MIDI_OUT)</source>
        <translation>MIDI PAR DÉFAUT
(ALIAS MIDI_OUT)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3718"/>
        <source>Default MIDI device</source>
        <translation>Périphérique MIDI par défaut</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3721"/>
        <source>Type here the default MIDI device used by messages containing the keyword midi_out</source>
        <translation>Taper ici le périphérique MIDI par défaut utilisé pour les messages contenant le mot-clef midi_out</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3740"/>
        <source>SERIAL PORT</source>
        <translation>PORT SÉRIE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3753"/>
        <source>Serial port address</source>
        <translation>Adresse du port série</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3756"/>
        <source>Type here the configuration of your serial port (syntax : port name:baud rate:data bits:parity:stop bits:flow control)</source>
        <translation>Taper ici la configration du port série (syntaxe : port name:baud rate:data bits:parity:stop bits:flow control)</translation>
    </message>
    <message>
        <source>Click here to refresh the MIDI in/out available devices</source>
        <translation type="obsolete">Cliquer ici pour rafraîchir la liste des périphériques MIDI in/out disponibles</translation>
    </message>
    <message>
        <source>Refresh MIDI devices</source>
        <translation type="obsolete">Rafraîchir la liste MIDI</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3778"/>
        <source>MIDI TEMPO
(FOR CLOCK SYNC.)</source>
        <translation>TEMPO MIDI
(HORLOGE MIDI)</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3798"/>
        <source>Score BPM</source>
        <translation>BPM de la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3801"/>
        <source>Type here the BPM (used by MIDI clock for sync)</source>
        <translation>Taper ici le BPM utilisé pour la synchronisation des horologes MIDI</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3819"/>
        <source>Check this option if you want to sync transport (play, pause, stop, fast rewind, song position) from another sequencer</source>
        <translation>Cocher cette case si vous souhaitez synchroniser le transport (play, pause, stop, retour à zéro, position temporelle) depuis un autre séquenceur</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3822"/>
        <source>SYNC TRANSPORT</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3829"/>
        <source>Check this option if you want to sync clock from another sequencer</source>
        <translation>Cocher cette case si vous souhaitez synchroniser l&apos;horloge avec un autre séquenceur</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3832"/>
        <source>SYNC CLOCK</source>
        <translation>SYNC HORLOGE</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3908"/>
        <source>Mouse position</source>
        <translation>Position de la souris</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3911"/>
        <source>Mouse current position on score</source>
        <translation>Position de la souris dans la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3918"/>
        <source>MOUSE</source>
        <translation>SOURIS</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3925"/>
        <source>Zoom</source>
        <translation>Zoom</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3928"/>
        <source>Score current zoom</source>
        <translation>Zoom actuel dans la partition</translation>
    </message>
    <message>
        <location filename="../uiinspector.ui" line="3935"/>
        <source>ZOOM</source>
        <translation>ZOOM</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="78"/>
        <source>Easing</source>
        <translation>Accéleration </translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="146"/>
        <source>Can&apos;t change ID.</source>
        <translation>Impossible de modifier l&apos;ID.</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="146"/>
        <source>Another object has this ID.
Try deleting that object, or change its ID.</source>
        <translation>Un autre objet possède déjà cet ID.
Essayez de supprimer cet objet ou changez son ID.</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="271"/>
        <source>IanniX Color Inspector</source>
        <translation>Inspecteur de couleurs</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="358"/>
        <location filename="../uiinspector.cpp" line="369"/>
        <source>IanniX Inspector</source>
        <translation>Inspecteur IanniX</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="358"/>
        <source>Enter the new ID:</source>
        <translation>Entez le nouvel ID de l&apos;objet :</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="369"/>
        <source>Enter the name of the destination group:</source>
        <translation>Entrez le nom du groupe :</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="397"/>
        <source>MOUSE:</source>
        <translation>SOURIS : </translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="400"/>
        <source>ZOOM:</source>
        <translation>ZOOM : </translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="560"/>
        <source>CURVE</source>
        <translation>COURBE</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="564"/>
        <source>CURSOR</source>
        <translation>CURSEUR</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="892"/>
        <source>No client connected</source>
        <translation>Aucune client connecté</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="894"/>
        <source>1 client connected</source>
        <translation>1 client connecté</translation>
    </message>
    <message>
        <location filename="../uiinspector.cpp" line="896"/>
        <source>%1 clients connected</source>
        <translation>%1 client connecté</translation>
    </message>
</context>
<context>
    <name>UiMessageBox</name>
    <message>
        <location filename="../uimessagebox.ui" line="14"/>
        <source>IanniX</source>
        <translation>IanniX</translation>
    </message>
    <message>
        <location filename="../uimessagebox.ui" line="284"/>
        <location filename="../uimessagebox.ui" line="365"/>
        <location filename="../uimessagebox.ui" line="406"/>
        <location filename="../uimessagebox.ui" line="423"/>
        <location filename="../uimessagebox.ui" line="493"/>
        <location filename="../uimessagebox.ui" line="513"/>
        <source>ENTER A VALUE FOR</source>
        <translation>ENTRER UNE VALEUR POUR</translation>
    </message>
    <message>
        <location filename="../uimessagebox.ui" line="335"/>
        <location filename="../uimessagebox.ui" line="471"/>
        <source>PICTURE</source>
        <translation>IMAGE</translation>
    </message>
</context>
<context>
    <name>UiRender</name>
    <message utf8="true">
        <location filename="../uirender.ui" line="14"/>
        <source>IanniX — Render</source>
        <translation>IanniX — Rendu</translation>
    </message>
    <message>
        <location filename="../uirender.ui" line="17"/>
        <location filename="../uirender.cpp" line="89"/>
        <source>Click+move and mouse wheel to navigate/zoom in score. In 3D, Alt+move, Alt+mouse wheel and Alt+double-click to change camera position. Double-clic on an object to edit messages. Shift+double-clic on an object to force its messages to be sent.</source>
        <translation>Cliquer-déplacer/mollette pour naviguer/zoomer dans la partition. En 3D, Alt+déplacer/Alt+molette et Alt+double-click pour déplacer la caméra. Double-clic sur un objet pour éditer ses messages. Shift+double-click sur un objet pour forcer un envoi de message.</translation>
    </message>
    <message>
        <location filename="../uirender.cpp" line="216"/>
        <source>Image_%1.png</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uirender.cpp" line="951"/>
        <source>IanniX Curve Resample</source>
        <translation>Rééchantionnage de courbes</translation>
    </message>
    <message>
        <location filename="../uirender.cpp" line="951"/>
        <source>Number of points:</source>
        <translation>Nombre de points :</translation>
    </message>
    <message>
        <location filename="../uirender.cpp" line="1055"/>
        <source>Image dropâ¦</source>
        <translation>Glisser-déposer d&apos;image</translation>
    </message>
    <message>
        <location filename="../uirender.cpp" line="1055"/>
        <source>Please select the desired action:</source>
        <translation>Veuillez sélectionner une action à réaliser :</translation>
    </message>
    <message>
        <location filename="../uirender.cpp" line="1055"/>
        <location filename="../uirender.cpp" line="1058"/>
        <source>Use this image as a background</source>
        <translation>Utiliser cette image comme fond de la partition</translation>
    </message>
    <message>
        <location filename="../uirender.cpp" line="1055"/>
        <source>Try to vectorize this image automaticaly</source>
        <translation>Essayer de vectoriser automatiquement l&apos;image</translation>
    </message>
    <message>
        <location filename="../uirender.h" line="106"/>
        <source>Click on score to add points. Double-click or press ESC to end your curve. After, Double-click on a curve to add a point, Command+click to remove it, Double-click on a point to enable/disable smoothing. Shift+double-click to resample curve.</source>
        <translation>Cliquer pour ajouter des points. Double-click ou ESC pour finir une courbe. Ensuite, Double-clic sur la courbe pour ajouter un point, Command+click pour le supprimer, Double-click sur un point pour activer/désactiver le lissage. Shift+double-click pour rééchantilloner la courbe.</translation>
    </message>
    <message>
        <location filename="../uirender.h" line="108"/>
        <source>Click on score to add points. Double-click or press ESC to end your curve. After, Double-click on a curve to add a point, Control+click to remove it, Double-click on a point to enable/disable smoothing. Shift+double-click to resample curve.</source>
        <translation>Cliquer pour ajouter des points. Double-click ou ESC pour finir une courbe. Ensuite, Double-clic sur la courbe pour ajouter un point, Control+click pour le supprimer, Double-click sur un point pour activer/désactiver le lissage. Shift+double-click pour rééchantilloner la courbe.</translation>
    </message>
</context>
<context>
    <name>UiSplash</name>
    <message>
        <location filename="../uisplash.ui" line="26"/>
        <source>IanniX</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uisplash.cpp" line="31"/>
        <source>version</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uisplash.cpp" line="31"/>
        <source>beta</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>UiTimer</name>
    <message>
        <location filename="../uitimer.ui" line="14"/>
        <source>IanniX - Timer</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uitimer.ui" line="38"/>
        <source>000:00.000</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>UiTransport</name>
    <message utf8="true">
        <location filename="../uitransport.ui" line="14"/>
        <source>IanniX — Transport</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="178"/>
        <source>Fast rewind</source>
        <translation>Retour à zéro</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="181"/>
        <source>Press this button to fast rewind the playback</source>
        <translation>Appuyer sur ce bouton pour revenir à zéro</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="213"/>
        <source>Play/pause</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="216"/>
        <source>Press this button to start or pause the playback</source>
        <translation>Appuyer sur ce bouton pour démarrer ou mettre en pause le playback</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="294"/>
        <source>Elapsed time</source>
        <translation>Temps écoulé</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="297"/>
        <source>This area display the elapsed time from the beginning of the playback</source>
        <translation>Cette zone affiche le temps écoulé depuis le début du playback</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="355"/>
        <source>Sent messages</source>
        <translation>Messages envoyés</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="358"/>
        <source>This area displays the sent messages by IanniX</source>
        <translation>Cette zone affiche les messages envoyés par IanniX</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="361"/>
        <source>No message</source>
        <translation>Pas de message</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="379"/>
        <location filename="../uitransport.ui" line="413"/>
        <source>Playback speed</source>
        <translation>Vitesse du playback</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="382"/>
        <source>Move this slider to adjust the global playback speed</source>
        <translation>Déplacer le slider pour ajuster la vitesse générale du plauback</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="416"/>
        <source>Change this spinbox to adjust the global playback speed</source>
        <translation>Modifier ce champ pour ajuster la vitesse générale du playback</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="489"/>
        <source>Scheduler period</source>
        <translation>Période du scheduler</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="492"/>
        <source>Report of the time between two calculations or type directly in this box to change it manually </source>
        <translation>Affiche le temps écoulé entre deux calculs de la partition (positions des curseurs et déclenchements des triggers). Vous pouvez aussi changer la valeur directement dans le champ</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="520"/>
        <source>Frames per seconds</source>
        <translation>Images par secondes</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="523"/>
        <source>Displays of the number of frames per seconds or type directly in this box to change it manually </source>
        <translation>Affiche le nombre d&apos;images par secondes. Vous pouvez aussi changer la valeur directement dans le champ</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="551"/>
        <source>Click here to enable or disable Syphon output (video frame exchange between Mac OS apps)</source>
        <translation>Cliquer ici pour activer ou désactiver la sortie vidéo dans Syphon (protocole d&apos;échange d&apos;image entre applications Mac OS)</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="554"/>
        <source>Syphon</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="627"/>
        <source>About IanniX</source>
        <translation>À propos de IanniX</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="630"/>
        <source>Click here to display information about IanniX</source>
        <translation>Cliquer ici pour afficher les informations relatives à IanniX</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="665"/>
        <source>CPU usage</source>
        <translation>Usage CPU</translation>
    </message>
    <message>
        <location filename="../uitransport.ui" line="668"/>
        <source>Report of the CPU usage</source>
        <translation>Affiche l&apos;utilisation CPU de IanniX</translation>
    </message>
</context>
<context>
    <name>UiView</name>
    <message utf8="true">
        <location filename="../uiview.ui" line="14"/>
        <source>IanniX — View</source>
        <translation>IanniX</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="157"/>
        <source>PERFORMANCE MODE</source>
        <translation>MODE PERFORMANCE</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="167"/>
        <source>PREVIEW</source>
        <translation>APERÇU</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="209"/>
        <source>Edit</source>
        <translation>Éditer</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="234"/>
        <source>File</source>
        <translation>Fichier</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="258"/>
        <source>Display</source>
        <translation>Afficher</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="262"/>
        <source>Grid setup</source>
        <translation>Réglage de la grille</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="296"/>
        <source>Playback</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="303"/>
        <source>Arrange objects</source>
        <translation>Aligner les objets</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="307"/>
        <source>Align horizontally</source>
        <translation>Aligner horizontalement</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="315"/>
        <source>Align vertically</source>
        <translation>Aligner verticalement</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="349"/>
        <source>Transport</source>
        <translation>Transport</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="370"/>
        <source>Inspector</source>
        <translation>Inspecteur</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="379"/>
        <source>Toolbar</source>
        <translation>Barre d&apos;outils</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="420"/>
        <source>Undo</source>
        <translation>Annuler</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="423"/>
        <source>Click here to undo last action</source>
        <translation>Cliquer ici pour annuler la dernière action</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="426"/>
        <source>Ctrl+Z</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="434"/>
        <source>Redo</source>
        <translation>Refaire</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="437"/>
        <source>Click here to redo last action</source>
        <translation>Cliquer ici pour répéter la dernière action</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="440"/>
        <source>Ctrl+Y</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="448"/>
        <source>Copy</source>
        <translation>Copier</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="451"/>
        <source>Click here to copy selected objects in clipboard</source>
        <translation>Cliquer ici pour copier les objets sélectionnés dans le presse-papier</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="454"/>
        <source>Ctrl+C</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="462"/>
        <source>Paste</source>
        <translation>Coller</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="465"/>
        <source>Click here to paste copied objects from clipboard</source>
        <translation>Cliquer ici pour coller les objets du presse-papier</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="468"/>
        <source>Ctrl+V</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="476"/>
        <source>Cut</source>
        <translation>Couper</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="479"/>
        <source>Click here to copy and remove selected objects</source>
        <translation>Cliquer ici pour copier et supprimer les objets sélectionnés</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="482"/>
        <source>Ctrl+X</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="490"/>
        <source>Select all</source>
        <translation>Tout sélectionner</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="493"/>
        <source>Click here to select all the selectable objects in the score</source>
        <translation>Cliquer ici pour sélectionner tous les objetsn sélectionnables de la partition</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="496"/>
        <source>Ctrl+A</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="504"/>
        <source>Delete</source>
        <translation>Supprimer</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="507"/>
        <source>Click here to remove selected objects</source>
        <translation>Cliquer ici pour supprimer les objets sélectionnés</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="510"/>
        <source>Backspace</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="518"/>
        <source>New score</source>
        <translation>Nouvelle partition</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="521"/>
        <source>Create a new score</source>
        <translation>Créer une nouvelle partition</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="524"/>
        <source>Click here to create a new empty score</source>
        <translation>Cliquer ici pour créer un nouvelle partition vierge</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="527"/>
        <source>Ctrl+N</source>
        <translation></translation>
    </message>
    <message utf8="true">
        <location filename="../uiview.ui" line="535"/>
        <source>Open project folder…</source>
        <translation>Ouvrir un projet…</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="538"/>
        <source>Click here to open a folder of scores</source>
        <translation>Cliquer ici pour ouvrir le dossier des partitions</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="541"/>
        <source>Ctrl+O</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="549"/>
        <source>Save current score</source>
        <translation>Sauvegarder la partition</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="552"/>
        <source>Click here to save the current score</source>
        <translation>Cliquer ici pour sauvegarder la partition courante</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="555"/>
        <source>Ctrl+S</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="563"/>
        <source>Quit</source>
        <translation>Quitter</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="566"/>
        <source>Click here to quit IanniX</source>
        <translation>Cliquer ici pour quitter IanniX</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="569"/>
        <source>Ctrl+Q</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="587"/>
        <source>Fullscreen</source>
        <translation>Plein écran</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="590"/>
        <source>Click here to switch to fullscreen</source>
        <translation>Cliquer ici pour activer le plein-écran</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="593"/>
        <source>Ctrl+F</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="611"/>
        <source>Inspector panel</source>
        <translation>Inspecteur</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="614"/>
        <source>Click here to hide/show inspector panel</source>
        <translation>Cliquer ici pour afficher/cacher l&apos;inspecteur</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="617"/>
        <source>Ctrl+Alt+I</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="635"/>
        <source>Transport panel</source>
        <translation>Transport</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="638"/>
        <source>Click here to hide/show transport panel</source>
        <translation>Cliquer ici pour afficher/cacher la barre de transport</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="641"/>
        <source>Ctrl+Alt+T</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="649"/>
        <source>Play/pause</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="652"/>
        <source>Click here to play or pause the playback</source>
        <translation>Cliquer ici pour démarrer ou mettre en pause le playback</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="655"/>
        <source>Space</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="663"/>
        <source>Fast rewind</source>
        <translation>Retour à zéro</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="666"/>
        <source>Click here to fast rewind the playback</source>
        <translation>Cliquer ici pour remettre à zéro le playback</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="669"/>
        <source>F</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="687"/>
        <source>Grid &amp;&amp; axis</source>
        <translation>Grille &amp;&amp; axes</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="690"/>
        <source>Click here to show/hide score grid and axis</source>
        <translation>Cliquer ici pour afficher/cacher la grille et les axes</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="693"/>
        <source>Ctrl+G</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="701"/>
        <source>Duplicate</source>
        <translation>Dupliquer</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="704"/>
        <source>Click here to duplicate selected objects</source>
        <translation>Cliquer ici pour dupliquer les objets sélectionnés</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="707"/>
        <source>Ctrl+D</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="721"/>
        <source>Autoresize object</source>
        <translation>Redimensionnement automatique des objets</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="724"/>
        <source>Click here to rescale objects according to zoom</source>
        <translation>Cliquer ici pour redimensionner automatiquement les objets en fonction du zoom</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="727"/>
        <source>Ctrl+Shift+A</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="735"/>
        <source>Zoom in</source>
        <translation>Zoomer</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="738"/>
        <source>Click here to zoom in</source>
        <translation>Cliquer ici pour zoomer</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="741"/>
        <source>Ctrl+=</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="749"/>
        <source>Zoom out</source>
        <translation>Dézoomer</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="752"/>
        <source>Click here to zoom out</source>
        <translation>Cliquer ici pour dézoomer</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="755"/>
        <source>Ctrl+-</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="763"/>
        <source>Initial zoom</source>
        <translation>Zoom initial</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="766"/>
        <source>Click here to restore initial zoom</source>
        <translation>Cliquer ici pour restaurer le zoome initial</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="769"/>
        <source>Ctrl+Shift+0</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="784"/>
        <source>Draw a smooth curve</source>
        <translation>Dessiner une courbe lissée</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="787"/>
        <source>Click here to add and draw a smooth curve in your score. Press ESC or click again to end your curve.</source>
        <translation>Cliquer ici pour ajouter et dessiner une courbe lissée dans la partition. Appuyer sur ESC ou recliquer ici pour finir la courbe.</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="790"/>
        <source>Ctrl+Shift+F</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="805"/>
        <source>Draw straight curve</source>
        <translation>Dessiner une courbe</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="808"/>
        <source>Click here to add and draw a straight curve in your score. Press ESC or click again to end your curve.</source>
        <translation>Cliquer ici pour ajouter et dessiner une courbe dans la partition. Appuyer sur ESC ou recliquer ici pour finir la courbe.</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="811"/>
        <source>Ctrl+Shift+G</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="826"/>
        <source>Add triggers</source>
        <translation>Ajouter des triggers</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="829"/>
        <source>Click here to add triggers in your score. Press ESC or click again to stop adding triggers.</source>
        <translation>Cliquer ici pour ajouter des triggers dans la partition. Appuyer sur ESC ou recliquer ici pour terminer l&apos;ajout.</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="832"/>
        <source>Ctrl+Shift+T</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="844"/>
        <source>Add a cursor</source>
        <translation>Ajouter un curseur</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="847"/>
        <source>Click here to add cursors on the selected curve. If no curve is selected, cursor will be free (controlled by an external source)</source>
        <translation>Cliquer ici pour ajouter des curseurs sur la courbe sélectionnée. Si aucune courbe est sélectionnée, le curseur sera libre (contrôlé par exemple depuis une source externe)</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="858"/>
        <source>10 seconds</source>
        <translation>10 secondes</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="872"/>
        <source>1 second</source>
        <translation>1 seconde</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="883"/>
        <source>500 milliseconds</source>
        <translation>500 millisecondes</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="894"/>
        <source>100 milliseconds</source>
        <translation>100 millisecondes</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="905"/>
        <source>10 milliseconds</source>
        <translation>10 millisecondes</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="916"/>
        <source>Custom value</source>
        <translation>Valeur personnalisée</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="927"/>
        <source>100% opaque</source>
        <translation>100% d&apos;opacité</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="935"/>
        <source>75% opaque</source>
        <translation>75% d&apos;opacité</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="946"/>
        <source>50% opaque</source>
        <translation>50% d&apos;opacité</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="954"/>
        <source>25% opaque</source>
        <translation>25% d&apos;opacité</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="962"/>
        <source>10% opaque</source>
        <translation>10% d&apos;opacité</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="974"/>
        <source>Add circular curves</source>
        <translation>Ajouter une courbe circulaire</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="977"/>
        <source>Click here to add circular curves in your score. Press ESC or click again to stop adding circular cuvers.</source>
        <translation>Cliquer ici pour ajouter une courbe circlaire dans la partition. Appuyer sur ESC ou recliquer ici pour finir la courbe.</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="980"/>
        <source>Ctrl+Shift+R</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="992"/>
        <source>Help</source>
        <translation>Aide</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="995"/>
        <source>Click here to display IanniX help in your browser</source>
        <translation>Cliquer ici pour afficher l&apos;aide de IanniX dans le navigateur</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1010"/>
        <source>Snap to X-grid</source>
        <translation>Grille magnétique sur X</translation>
    </message>
    <message utf8="true">
        <location filename="../uiview.ui" line="1013"/>
        <location filename="../uiview.ui" line="1328"/>
        <location filename="../uiview.ui" line="1349"/>
        <source>Click here to snap actions (objects position, curve points…) to grid</source>
        <translation>Cliquer ici pour activer/désactiver la grille magnétique</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1016"/>
        <source>Shift+G</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1024"/>
        <location filename="../uiview.ui" line="1027"/>
        <location filename="../uiview.ui" line="1030"/>
        <source>Save all scores</source>
        <translation>Sauvegarder toutes les partitions</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1033"/>
        <source>Click here to save all the opened scores</source>
        <translation>Cliquer ici pour sauvegarder toutes les partitions ouvertes</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1036"/>
        <source>Ctrl+Alt+Shift+S</source>
        <translation></translation>
    </message>
    <message utf8="true">
        <location filename="../uiview.ui" line="1044"/>
        <source>Rename score…</source>
        <translation>Renommer la partition…</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1047"/>
        <source>Click here to rename your score</source>
        <translation>Cliquer ici pour renommer la partition</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1050"/>
        <source>Ctrl+Alt+Shift+R</source>
        <translation></translation>
    </message>
    <message utf8="true">
        <location filename="../uiview.ui" line="1058"/>
        <source>Remove score from project folder…</source>
        <translation>Supprimer la partition…</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1061"/>
        <source>Click here to remove this score from your project folder</source>
        <translation>Cliquer ici pour supprimer la partition du projet</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1069"/>
        <source>Duplicate score in project folder</source>
        <translation>Dupliquer la partition</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1072"/>
        <source>Click here to duplicate your score in your project folder</source>
        <translation>Cliquer ici pour dupliquer la partition</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1087"/>
        <source>Lock objects position</source>
        <translation>Vérouiller la position des objets</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1090"/>
        <source>Click here to lock/unlock the position of objects (to avoid moving objects while navigating in the score)</source>
        <translation>Cliquer ici vérouiller/dévérouiller la position des objets (pour éviter de déplacer les objets en naviguant dans la partition)</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1108"/>
        <source>Objects labels</source>
        <translation>Étiquette des objets</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1111"/>
        <source>Click here to show/hide labels on objects</source>
        <translation>Cliquer ici pour afficher/cacher les étiquette des objets</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1119"/>
        <source>Open patches folder</source>
        <translation>Ouvrir le dossier des patches</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1122"/>
        <source>Click here to open the patches folder (external objects for hosts software) provided with IanniX</source>
        <translation>Cliquer ici pour le dossier des patches (objets pour les logiciels hôtes) fourni avec IanniX</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1130"/>
        <source>About IanniX</source>
        <translation>À propos de IanniX</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1133"/>
        <source>Click here to display information about IanniX</source>
        <translation>Cliquer ici pour afficher des informations sur IanniX</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1144"/>
        <source>Send score through default sync output</source>
        <translation>Envoyer la partition sur le port de synchronisation</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1147"/>
        <source>Click here to send your score through the default sync output</source>
        <translation>Cliquer ici pour envoyer la partition via le port de synchronisation</translation>
    </message>
    <message utf8="true">
        <location filename="../uiview.ui" line="1155"/>
        <source>Import SVG as a curve…</source>
        <translation>Importer une courbe à partir d&apos;un SVG…</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1158"/>
        <source>Click here to import a SVG file as a curve in your score</source>
        <translation>Cliquer ici pour importer une courbe à partir d&apos;un fichier SVG</translation>
    </message>
    <message utf8="true">
        <location filename="../uiview.ui" line="1166"/>
        <source>Import image to be vectorized…</source>
        <translation>Importer une courbe à partir d&apos;une image…</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1169"/>
        <source>Click here to import image to be vectorized in your score</source>
        <translation>Cliquer ici pour importer une courbe à partir d&apos;une image vectorisée automatiquement</translation>
    </message>
    <message utf8="true">
        <location filename="../uiview.ui" line="1177"/>
        <source>Import glyph as a curve…</source>
        <translation>Importer une courbe à partir d&apos;un glyphe…</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1180"/>
        <source>Click here to import a glyph as a curve in your score</source>
        <translation>Cliquer ici pour importer une courbe à partir d&apos;un glyphe</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1198"/>
        <source>Script editor window</source>
        <translation>Fenêtre d&apos;éditeur de script</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1201"/>
        <source>Click here to show the script editor window (if you&apos;re working on a script)</source>
        <translation>Cliquer ici pour afficher l&apos;éditeur de script (si vous travaillez dans un script)</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1204"/>
        <source>Ctrl+E</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1212"/>
        <source>Reload current script</source>
        <translation>Recharger le script</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1215"/>
        <source>Click here to reload the current script</source>
        <translation>Cliquer ici pour recharger le script</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1218"/>
        <source>Ctrl+R</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1233"/>
        <source>Lighter color theme</source>
        <translation>Thème de couleur lumineux</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1236"/>
        <source>Click here to change the color theme of IanniX</source>
        <translation>Cliquer ici pour changer le thème de couleurs de IanniX</translation>
    </message>
    <message utf8="true">
        <location filename="../uiview.ui" line="1244"/>
        <source>Import a background image…</source>
        <translation>Importer une image de fond…</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1247"/>
        <source>Click here to import a background image in your score</source>
        <translation>Cliquer ici pour importer une image de fond</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1265"/>
        <source>Allow triggers selection</source>
        <translation>Autoriser la sélection des triggers</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1268"/>
        <source>Click here to allow/forbid the selection of triggers (on hover, on marquee selection, on select all actions)</source>
        <translation>Cliquer ici pour autoriser/interdire la sélection des triggers (sur toutes les actions de sélection)</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1286"/>
        <source>Allow curves selection</source>
        <translation>Autoriser la sélection des courbes</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1289"/>
        <source>Click here to allow/forbid the selection of curves (on hover, on marquee selection, on select all actions)</source>
        <translation>Cliquer ici pour autoriser/interdire la sélection des courbes (sur toutes les actions de sélection)</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1307"/>
        <source>Allow cursors selection</source>
        <translation>Autoriser la sélection des curseurs</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1310"/>
        <source>Click here to allow/forbid the selection of cursors (on hover, on marquee selection, on select all actions)</source>
        <translation>Cliquer ici pour autoriser/interdire la sélection des curseurs (sur toutes les actions de sélection)</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1325"/>
        <source>Snap to Y-grid</source>
        <translation>Grille magnétique sur Y</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1331"/>
        <source>Shift+H</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1346"/>
        <source>Snap to grid</source>
        <translation>Grille magnétique</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1357"/>
        <location filename="../uiview.ui" line="1360"/>
        <source>Copy as a script</source>
        <translation>Copier comme un script</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1363"/>
        <source>Click here to copy selected objects in clipboard as script commands</source>
        <translation>Cliquer ici pour copier le script générant les objets sélectionnés dans le presse-papier</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1366"/>
        <source>Ctrl+Shift+C</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1374"/>
        <location filename="../uiview.ui" line="1377"/>
        <source>Paste as a script</source>
        <translation>Coller comme un script</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1380"/>
        <source>Click here to paste scripts commands from clipboard (a script must be loaded before)</source>
        <translation>Cliquer ici pour coller du script provenant du presse-papier</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1383"/>
        <source>Ctrl+Shift+V</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1391"/>
        <source>Distribute horizontally</source>
        <translation>Répartir horizontalement</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1394"/>
        <source>Click here to distribute objects horizontally from the leftmost object to the rightmost object</source>
        <translation>Cliquer ici pour répartir les objets horizontalement, de l&apos;objet le plus à gauche à l&apos;objet le plus à droite</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1402"/>
        <source>Distribute vertically</source>
        <translation>Répartir verticalement</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1405"/>
        <source>Click here to distribute objects vertically from the topmost object to the bottommost object</source>
        <translation>Cliquer ici pour répartir les objets verticalement, de l&apos;objet le plus haut à l&apos;objet le plus bas</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1413"/>
        <source>Align left</source>
        <translation>Aligner à gauche</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1416"/>
        <source>Click here to align objects on the leftmost object</source>
        <translation>Cliquer ici pour aligner les objets sur l&apos;objet le plus à gauche</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1424"/>
        <source>Align center</source>
        <translation>Aligner au centre</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1427"/>
        <source>Click here to align objects on the horizontal center of the selection</source>
        <translation>Cliquer ici pour aligner les objets sur le centre de la sélection</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1435"/>
        <source>Align right</source>
        <translation>Aligner à droite</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1438"/>
        <source>Click here to align objects on the rightmost object</source>
        <translation>Cliquer ici pour aligner les objets sur l&apos;objet le plus à droite</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1446"/>
        <source>Align top</source>
        <translation>Aligner en haut</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1449"/>
        <source>Click here to align objects on the topmost object</source>
        <translation>Cliquer ici pour aligner les objets sur l&apos;objet le plus haut</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1457"/>
        <source>Align middle</source>
        <translation>Aligner au milieu</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1460"/>
        <source>Click here to align objects on the vertical center of the selection</source>
        <translation>Cliquer ici pour aligner les objets sur le milieu de la sélection</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1468"/>
        <source>Align bottom</source>
        <translation>Aligner en bas</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1471"/>
        <source>Click here to align objects on the bottommost object</source>
        <translation>Cliquer ici pour aligner les objets sur l&apos;objet le plus bas</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1479"/>
        <source>Distribute circulary</source>
        <translation>Répartir circulairement</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1482"/>
        <source>Click here to align objects as a circle</source>
        <translation>Cliquer ici pour aligner les objets en forme de cercle</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1490"/>
        <source>Distribute on ellipse</source>
        <translation>Répartir en ellipse</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1493"/>
        <source>Click here to align objects as an ellipse</source>
        <translation>Cliquer ici pour aligner les objets en forme d&apos;ellipse</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1501"/>
        <source>Make a high resolution snapshot</source>
        <translation>Faire une capture haute-résolution</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1504"/>
        <source>Click here to save the current view in a high resolution PNG file (file will be placed on your desktop)</source>
        <translation>Cliquer ici pour exporter la vue courant dans un PNG haute-résolution (le fichier sera placé sur le bureau)</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1507"/>
        <source>Ctrl+Shift+P</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1560"/>
        <source>Performance mode</source>
        <translation>Mode performance</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1563"/>
        <source>Click here to switch to performance mode</source>
        <translation>Cliquez ici pour activer le mode performance</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1566"/>
        <source>Ctrl+P</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1515"/>
        <location filename="../uiview.cpp" line="451"/>
        <source>Resize viewport</source>
        <translation>Redimensionner la partition</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1518"/>
        <source>Click here to resize the viewport (the rendering area). Note that it is recommended to hide Transport bar and Inspector bar to get the exact desired size.</source>
        <translation>Cliquer ici pour redimensionner la partition (zone de rendu). Il est recommendé de cacher l&apos;inspecteur ainsi que la barre de transport pour obtenir la taille exacte.</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1536"/>
        <location filename="../uiview.ui" line="1539"/>
        <source>Timer window</source>
        <translation>Fenêtre de timer</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1542"/>
        <source>Click here to show the timer window, displaying elapsed time</source>
        <translation>Cliquer ici pour afficher la fenêtre du timer, affichant le temps-écoulé du playback</translation>
    </message>
    <message>
        <location filename="../uiview.ui" line="1545"/>
        <source>Ctrl+T</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="202"/>
        <source>FULLSCREEN ON DISPLAY %1 (%2 x %3)</source>
        <translation>PLEIN ÉCRAN SUR SORTIE %1 (%2 x %3)</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="327"/>
        <source>Select a SVG fileâ¦</source>
        <translation>Sélectionner un fichier SVG</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="327"/>
        <source>SVG Files</source>
        <translation>Fichiers SVG</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="332"/>
        <location filename="../uiview.cpp" line="337"/>
        <source>Select an imageâ¦</source>
        <translation>Sélectionner une image</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="332"/>
        <location filename="../uiview.cpp" line="337"/>
        <source>Images</source>
        <translation>Images</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="343"/>
        <source>Type a glyph or textâ¦</source>
        <translation>Tapez un glyphe ou un texte</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="343"/>
        <source>Type a glyphe or a text to import in IanniX:</source>
        <translation>Tapez un glyphe ou un texte à importer dans IanniX :</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="350"/>
        <source>Snaptshot</source>
        <translation>Capture</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="350"/>
        <source>Snapshot will be saved on your desktop.
Please enter a scale factor:</source>
        <translation>La capture va être sauvegardée sur le bureau.
Veuillez saisir un facteur de taille :</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="406"/>
        <source>Custom grid value</source>
        <translation>Grille personnalisée</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="406"/>
        <source>Enter the desired grid time value in seconds:</source>
        <translation>Veuillez saisir la grille désirée en secondes :</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="408"/>
        <source>Custom value:</source>
        <translation>Valeur:</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="408"/>
        <source>sec</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="451"/>
        <source>New viewport size</source>
        <translation>Redimensionner la partition</translation>
    </message>
    <message>
        <location filename="../uiview.cpp" line="451"/>
        <source>%1 x %2</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../uiview.h" line="108"/>
        <source>EN</source>
        <translation>FR</translation>
    </message>
</context>
</TS>
