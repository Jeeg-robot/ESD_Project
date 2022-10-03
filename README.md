# ESD_Project
Repo for ESD Project 

Saranno creati diversi branch ognuno per ogni membro in modo da non intralciare il lavoro degli altri. 
Questo file viene usato per descrivere in linee generali il progetto.

Nel seguente documento si cerca di buttare giù qualche idea oltre che identificare eventuali problematiche relativi alla idea.

VASO SMART 
 
In tale progetto l’obiettivo è di rendere “smart” un vaso per la coltivazione. In particolare gli elementi potenzialmente da aggiungere sono i seguenti: 
1.1)sensore di umidità
1.2) array di led rgb controllati dal micro 
1.3) sensore di pressione/sensore di misurazione dell’acqua in aggiunta con piccolo servo motore per far uscire più o meno acqua
1.4) Modulo batteria + usb type c
Queste 3 tasks sono indipendenti l’una dall’altra quindi una modifica o riduzione non influisce sul resto.
 
Nel caso del punto 1.1 le idee potrebbero essere le seguenti 2:
1.1.1)Il dato fornito dal sensore può essere visualizzato su un mini lcd display collegato al micro.
1.1.2)Il dato fornito dal sensore può essere usato per scegliere se più o meno aggiungere tramite acqua tramite il sistema 1.3)

Nel caso 1.2) l’idea sarebbe quella di controllare dei led che permettono di illuminare la pianta mediante circuiteria dedicata tramite un segnale di controllo PWM. 

Nel caso 1.3) le papabili soluzioni/idee sono le seguenti:
1.3.1) mediante un sensore di pressione posizionato sul fondale del recipiente oppure un sensore di misurazione dell’acqua viene utilizzato per sviluppare un sistema PI per controllare la quantità di acqua che viene fornita al sistema. Viene utilizzata anche l’info proveniente dal sistema 1.2) per decidere quando è necessario far uscire l’acqua.
1.3.2) viene utilizzato un semplice servo motore per far uscire l’acqua per un certo lasso di tempo. L’erogazione dell’acqua può avvenire tramite un pulsante o interruttore.

Il punto 1.4) riguarda l’alimentazione della scheda con l’aggiunta di un controllore per l’uso della porta USB type C

PROS: Non eccessiva complessità software, utilizzo di sensori economici, tensioni e correnti di lavoro basse, facile prototipazione, test separati delle singole fasi

CONTRO:discreta quantità di circuiteria di condizionamento per i sensori e per la parte di alimentazione e per i LED—>complessità PCB 
