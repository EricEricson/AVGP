# Audio-, Video-, Grafikprogrammierung
## MCI- und WPF-Anwendungen

# Inhaltsverzeichnis
1. [MCI Anwendung](#mci)
2. [WPF Anwendung](#wpf)
3. [DirectSound](#dxSound)
4. [Direct3D](#dx3D)
5. [DirectShow](#dxShow)

<a name="mci"/></a>
### Aufgabe 1: Audio-/Midi-/Video-Player (mit der CMCIObject-Klasse)
Implementieren Sie ein Programm das mit Hilfe der Klasse CMCIObject die Ausgabe einer Audiodatei im wav- oder mp3-Format ermöglicht [1P]. Erweitern Sie das Programm um zwei weitere Schaltflächen, mit deren Hilfe der Nutzer eine Ihnen im Praktikum zur Verfügung gestellte MIDI- und eine Video-Datei (im aktuellen Fenster) abspielen kann [1P].

Die Klasse CMCIObject ist um die Methoden SetAviPosition(...), TMSFSeek(...) und GetTMSFPosition(...) mit der in der Vorlesung besprochenen Funktionalität zu erweitern. Die Oberfläche Ihres Programms ist funktional entsprechend des hier dargestellten Screenshots zu gestalten [1P].

Erweitern Sie Ihr Programm dahingehend, das Schaltflächen zum Starten, Stoppen und Schließen der Wiedergabe einer Audio-CD, sowie zum gezielten Wechsel auf einzelne Titel der Audio-CD bereitstellt werden. Alle Titel der eingelegten Audio-CD sind ein einer ListBox mit Angabe der Titellänge aufzuführen. Außerdem ist während des Abspielvorgangs die aktuelle Titel-Nummer und die laufende Abspielzeit in einem geeigneten Intervall auszugeben [1P].
![alt text][photo01]

[photo01]: https://www.informatik.htw-dresden.de/~bruns/prakt_mm_prog_bild3.jpg "photo01"

Erweitern Sie die Klasse CMCIObject um eine Methode zur Ermittlung der Länge einer Mediendatei. Ergänzen Sie nun die Darstellung der Zeitanzeige um eine Prozentangabe zum Abspielfortschritt [1P]. Testen Sie Ihre Anwendung und machen Sie sich die Grenzen des Media Control Interface deutlich.

<a name="wpf"/>
###  Aufgabe 2: (Audio-) Video-Player (mit der Windows Presentation Foundation)
Implementieren Sie mit C# eine WPF Anwendung unter Nutzung der in der Vorlesung erarbeiteten Wrapperklasse. Hierzu ist die Grundfunktionalität (Play-, Pause-, Stopp) zum Abspielen einer Videodatei bereitzustellen [2P].
Eine weitere Schaltfläche dient zum Umschalten in den Vollbildmodus, der dann zum Beispiel mit der linken Maustaste wieder verlassen werden kann [1P]. 
![alt text][photo02]

[photo02]: https://www.informatik.htw-dresden.de/~bruns/prakt_mm_prog_bild_wpf.jpg "photo02"

Die aktuelle Abspielposition ist als Zeitangabe und prozentual auszugeben [1P].
Ein mitlaufender Slider dient zum Navigieren innerhalb des Videos. Zwei weitere Slider dienen der Einstellung von Lautstärke und Balance [1P]. 

**Termine:** Diese Aufgaben 1 und 2 werden in der 43., 44. und 45. KW bearbeitet. Die Punkte (PVL) können in der 45. KW erworben werden. 

## DirectX
<a name="dxSound"/>
###  Aufgabe 1: DirectSound
Implementieren Sie eine einfache Dialoganwendung und binden Sie die in der Vorlesung besprochene Klasse CDirectSound ein. Initialisieren Sie ein Objekt dieser Klasse und erzeugen Sie einen "Secondary DirectSoundBuffer" mit folgenden Eigenschaften:
* PCM-Format,
* stereo,
* 16 Bit pro Sample,
* 22.05 kHz Samplingrate,
* 4 Sekunden Pufferkapazität

![alt text][photo03]

[photo03]: https://www.informatik.htw-dresden.de/~bruns/prakt_mm_prog_bild2.jpg "photo03"

Schreiben Sie 2 Sekunden Sound mit einer Sinusamplitute und einer Frequenz von 264 Hz ("Ton c") in den Soundpuffer und spielen Sie diesen Soundpuffer zyklisch ab [1P].

Starten Sie mit Hilfe einer weiteren Schaltfläche einen Timer mit einer Periode von 700 Millisekunden. Die Timerereignisse sind derart zu behandeln, dass jeweils 2 Sekunden des Soundpuffers im Sinne der Doppelpuffertechnik verwendet werden. Während der eine Pufferteil abgespielt wird, werden Sinusamplituten der C-Durtonleiter mit steigender Frequenz in den jeweils anderen Pufferteil geschrieben. Nach einer Oktave endet die Wiedergabe [1P].

Implementieren Sie in Ihrem Programm die Möglichkeit, Lautstärke und Balanceeinstellungen zu beeinflussen.

Versuchen Sie mit Hilfe der Doppelpuffertechnik und der von Ihnen programmierten Klasse CDirectSound den Sound aus einer im Praktikum zur Verfügung gestellten pcm-Datei bis zum Ende abzuspielen. Beachten Sie, dass am Ende der Puffer wieder mit 0-Bytes zu füllen ist. Legen Sie sich für das Abspielen von PCM-Dateien eine geeignete weitere Methode der Klasse an [1P].

Wenn auf einem Instrument, wie z.B. einer Gitarre, Geige oder einem Klavier, ein Ton erzeugt wird, dann besteht dieser nicht nur aus einer einzigen Frequenz, sondern es schwingen noch verschiedene Obertöne mit. Man kann jedoch im Allgemeinen diesem Ton eine Grundfrequenz zuordnen. So ist dem Kammerton 'A' die Frequenz 440Hz zugeordnet oder dem Ton 'C' die Frequenz 264 Hz. Weitere Töne können über die folgende Tabelle bestimmt werden.

Die Musiktheorie besagt, dass die Tonabstände innerhalb einer Tonleiter in die Intervalle Prime, Sekunde, Terz, Quarte, Quinte, Sexte, Septime und Oktave eingeteilt sind. Nachfolgend ist als Beispiel eine C-Dur Tonleiter (reine Stimmung) und die dafür notwendigen Frequenzverhältnisse aufgeführt. Ähnliches gilt natürlich für Tonleitern in Moll.

Fügen Sie nun Ihrem Programm Schaltflächen (Buttons) für die einzelnen Töne einer Tonleiter hinzu und behandeln Sie das BN_CLICKED-Ereignis dahingehend, dass der jeweilige Ton kurz angespielt wird (je Ton ein eigener Soundpuffer). [1P].

Geben Sie nun dem Nutzer die Möglichkeit, über weitere Schaltflächen den C-Dur Dreiklang (als Akkord mit Hilfe von 3 Soundpuffern) abzuspielen.[1P].

Wir haben Ihnen im Praktikumsordner noch Gitarrentöne im pcm(raw)-Format (44.1 kHz Samplingrate, 16 Bit pro Sample, mono) bereitgestellt. Der Nutzer soll über eine geeignete Schaltfläche entscheiden können, ob er die oben genannte Funktionalität mit generiertem Sound oder Gitarrensound abgespielt bekommt. Optionale Zusatzpunkte: [3P]. 

<a name="dx3D"/>
###  Aufgabe 2: Direct3D
Erstellen Sie ein C++-Projekt (Dialoganwendung) mit Direct3D-Anbindung. Zur Initialisierung der Direct3D-Interfaces können Sie die auf dem Praktikumsordner (I:/PRAKT/bruns/DirectX/Direct3D) bereitgestellten Klassen in der aus der Vorlesung bekannten Beispielanwendung nutzen. Machen Sie sich hierzu deren Aufbau und Nutzung in dem Beispielprojekt deutlich, bevor Sie die Klassen in Ihr eigenes Projekt übernehmen. Erzeugen Sie ein einfaches 3D-Objekt aus 2 Rechtecken wie unten abgebildet. 

1. Zunächst soll dieses Objekt mit beliebiger Farbe dargestellt werden. Realisieren Sie über Transformationsmatrizen eine langsame Drehung (Rotation) um die x- und y-Achse [0.5P].
2. Messen Sie die aktuelle Framerate und zeigen diese im Fenster (entweder permanent oder auf Tastendruck) an [0.5P].
3. Ermöglichen Sie dem Nutzer, das Objekt auch mit der Maus (bei gedrückter linker Maustaste) zu bewegen [1P]. Nutzen Sie hierzu die in der Klasse CDirect3DObject implementierten Transformationsmatrizen.

Erweitern Sie Ihr Modell mit Texturkoordinaten und laden Sie eine beliebige Textur auf die entsprechenden Rechtecke [1P]. 

<a name="dxShow"/>
###  Aufgabe 3: DirectShow
Erstellen Sie ein Abspielprogramm für Videodateien. Die folgende Funktionalität ist dabei zu implementieren: 
- Der Dateiname ist über eine Dateidialogbox (CFileDialog) auszuwählen (oder via "Drag and Drop" an das Programm zu übermitteln) [1P].
- Das Abspielen erfolgt asynchron und das Video ist im aktuellen (Dialog)Fenster darzustellen [1P].
- Die aktuelle Abspielposition ist anzuzeigen (Textfeld und Schieberegler). Die aktuelle Abspielposition kann über den Schieberegler eingestellt werden. [1P]
- Die Ausgabe kann in den Vollbildmodus geschalten werden. Der Vollbildmodus kann mit der linken Maustaste wieder verlassen werden. Am Ende des Abspielvorgangs schaltet die Anwendung (automatisch) wieder in den Fenstermodus und an den Anfang des Videos. [1P]
- Kapseln Sie die Funktionalität von DirectShow sinnvoll und wiederverwendbar in einer eigenen Klasse [1P].
Nutzen Sie hierfür das in der Vorlesung entwickelte Beispiel und lassen Sie sich den Filtergraphen automatisch mit Hilfe der Methode "RenderFile" erstellen. Testen Sie Ihre Anwendung.
