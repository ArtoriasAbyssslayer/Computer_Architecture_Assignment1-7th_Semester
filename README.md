# Computer_Architecture_Assignment1-7th_Semester
## ΑΡΧΙΤΕΚΤΟΝΙΚΗ ΠΡΟΗΓΜΕΝΩΝ ΥΠΟΛΟΓΙΣΤΩΝ

### Αναφορά 1ου Εργαστηρίου 

#### Συγγραφείς : Σακελλαρίου Βασίλειος ΑΕΜ: 9400, Φίλης Χάρης ΑΕΜ:9449

**1) Ανάλυση του αρχείου : starter_se.py**

Από το αρχείο starter_se.py αναγνωρίζουμε τα εξής στοιχεία :

* Ορίζεται το dictionary cpu_types που αντιστοιχίζει τον επεξεργαστή σε έναν από τους παρακάτω τύπους(δομή δεδομένων):<br/>
       1) AtomicSimpleCPU : "atomic" ->Η προεπιλογή τύπου επεξεργαστή που δεν έχει caches.<br/>
       2) MinorCPU : "minor" ->Στην περίπτωση αυτή χρησιμοποιείται η βιβλιοθήκη devices.py που ορίζονται οι δομικές μονάδες του minor (L1 caches(dcache,icache), L2 cache) με όλα           τα χαρακτηριστικά τους.<br/>
       3) ΗPΙ : "hpi" ->Κατά αντιστοιχία με το παραπάνω μέσω της βιβλιοθήκης  HPI.py ορίζονται οι απαραίτητες μνήμες cache για hpi επεξεργαστή ή cluster.
       
* Ορίζεται στην κλάση _SimpleSeSystem_  η συχνότητα του ρολογιού : 
Clock speed: 1GHz στο πεδίο self.clk_domain = SrcClockDomain ( clock ="1GHz" , voltage_domain=self.voltage_domain )
* Στην main function ορίζονται από τον parser τα εξής:
     * Ο τύπος του επεξεργαστή, που στο δικό μας παράδειγμα επιλέγεται ο MinorCPU.
     * Caches: με την επιλογή minor cpu έχουμε και L1 cache και L2 cache, σύμφωνα με τις προδιαγραφές της βιβλιοθήκης devices.py
     * Μνήμη: με την εντολή που τρέχουμε δεν δίνουμε την παράμετρο --mem-size, άρα παίρνει την default τιμή που είναι τα 2Gb, ούτε και το --mem- type οπότε by default χρησιμοποιεί την τεχνολογία DDR3_1600_8x8.
     * Components voltage: default->3.3V.
     * CPU claster voltage: default->1.2V.
     * CPU freq: default->4Ghz.
     * Number of cores: default->1.



**2 a)**

Ανοίγοντας το αρχείο config.ini παρατηρούμε τα εξής :
* [system.clk_domain] -> clock = 1000 (επαληθεύεται)
* [system.cpu_cluster.cpus.dcache] -> size = 32768 (που επαληθεύεται από το αρχείο devices.py όπου η data cache L1 του minor είναι 32KB)
* [system.cpu_cluster.cpus.icache] -> size = 49152 (που επαληθεύεται από το αρχείο devices.py όπου η instruction cache L1 του minor είναι 48KB)
* [system.cpu_cluster.l2] -> size = 1048576 (που επαληθεύεται από το αρχείο devices.py όπου η cache L2 του minor είναι 1 ΜΒ)
* [system.voltage_domain] voltage=3.3(που επαληθεύεται) // χρησιμοποιείται από 0-5 γιατί πρόκειται για μικρουπολογιστές.
* [system.cpu_cluster.voltage_domain] -> voltage = 1.2(που επαληθεύεται) //Διαμοιράζεται το voltage που παίρνει το chip στα επιμέρους cpus.
* [system] -> _mem_ _ _ranges_ = 0 : 2147483648(που επαληθεύει τα 2GB by default DRAM)

**2b)**

Aνοίγοντας το αρχείο stats.txt κάνουμε τις παρακάτω παρατηρήσεις :<br/>
- Στο line14: system.cpu_cluster.cpus.committedInsts 5028 // Number of instructions committed<br/>
Commited intructions : 5028
- Στο line15 : system.cpu_cluster.cpus.committedOps 5834 //Number of ops (including micro ops)<br/>
Tο πρώτο αφορά τις εντολές του προγράμματος ενώ το δεύτερο προσθέτει σε αυτές και εντολές που διαμορφώνουν τον εξομοιωτή και τα δομικά του μέρη(πχ bootloader σε κινητά).

**2c)**

- Το συνολικό πλήθος των προσβάσεων στην L2 cache είναι 479, από τις οποίες 332 είναι από miss της icache και 147 από miss της dcache.
Αυτούσια παράθεση από το αρχείο stats.txt :<br/>
system.cpu_cluster.l2.demand_accesses::total : 479 // number of demand (read+write) accesses<br/>
system.cpu_cluster.l2.overall_accesses::.cpu_cluster.cpus.inst : 332 // number of overall (read+write) accesses<br/>
system.cpu_cluster.l2.overall_accesses::.cpu_cluster.cpus.data : 147 // number of overall (read+write) accesses.<br/>


**3)**
Συνοπτική περιγραφή των in-order μοντέλων επεξεργαστών με πληροφορίες που αντλήσαμε από [το site του gem5](http://www.gem5.org/documentation/) :

- **ΑtomicSimpleCPU :**

Ο ΑtomicSimple Cpu είναι μια εκδοχή SimpleCPU που παρέχει ο gem5 και χρησιμοποιεί atomic memory accesses. Σύμφωνα με το documentation του gem5 atomic accesses είναι  προσβάσεις στην μνήμη γρηγορότερες από τις λεπτομερείς (detailed accesses) και χρησιμοποιούνται για fast forwarding και warming up caches. O AtomicSimpleCPU εκτελεί όλες τις λειτουργίες για μια εντολή σε κάθε CPU tick(). 

- **TimingSimpleCPU :**

Ο TimingSimpleCPU είναι μια εκδοχή του SimpleCPU που παρέχει ο gem5 και χρησιμοποιεί timing memory accesses. Επειδή, το μοντέλο αυτό δεν έχει μνήμη cache σταματάει (stall) στα cache accesses και περιμένει από την κύρια μνήμη να ανταποκριθεί για να συνεχίσει την εκτέλεση της εντολής. Είναι επίσης, ένα fast-to-run μοντέλο, δεν υποστηρίζει pipelining, οπότε εκτελεί μόνο μία εντολή κάθε στιγμή. Τέλος, Atomic και Timing memory accesses δεν μπορούν να συνυπάρχουν σε ένα σύστημα μνήμης.*

(*) Timing accesses are the most detailed access. They reflect our best effort for realistic timing and include the modeling of queuing delay and resource contention. Once a timing request is successfully sent at some point in the future the device that sent the request will either get the response or a NACK if the request could not be completed (more below).

- **MinorCPU :**

O Μinor είναι ένας in-order επεξεργαστής με τέσσερα επίπεδα pipeline, με μοντελοποιήσιμες δομές δεδομένων και συμπεριφορά εκτέλεσης ώστε να μπορεί να εξομοιώνει όσο πιο κοντά γίνεται ένα πραγματικό επεξεργαστή. Τα 4 στάδια pipeline του minor είναι τα εξής (παράθεση στα αγγλικά, καθώς είναι δύσκολη η ταυτόσημη απόδοση τους στα ελληνικά) :

       1. Fetch1 :: Fetch1 is responsible for fetching cache lines or partial cache lines from the I-cache and passing them on to Fetch
       2. Fetch2 :: decomposes cache lines into instructions
       3. Decode :: takes a vector of instructions from Fetch2 (via its input buffer) and decomposes those instructions into micro-ops (if necessary) and 
          packs them into its output instruction vector
       4. Execute :: execution procedure

- **High-Performance In-order (HPI) CPU :**

Το μοντέλο αυτό είναι βασισμένο στην αρχιτεκτονική Arm και το ονομάζουμε HPI. To HPI CPU timing model ρυθμίζεται για να αντιπροσωπεύει μια μοντέρνα in-order Armv8-A εφαρμογή. Το pipeline του HPI CPU χρησιμοποιεί το ίδιο four-stage μοντέλο όπως ο MinorCPU που αναφέραμε παραπάνω.

 Όταν αλλάζουμε συχνότητα επεξεργαστή μας ενδιαφέρει το sys_clk (το ρολόι του συστήματος).

**a)** Το πρόγραμμα σε c που υλοποιήσαμε παράγει έναν τυχαίο αριθμό και συγκρίνουμε αν αυτός είναι μεγαλύτερος ή μικρότερος του 5.

Για την πρώτη προσομοίωση τρέχουμε το εξής για τον επεξεργαστή MinorCPU:
**./ build /ARM/gem5. opt −d ~/Desktop/MinorCPUdefault configs /example/ se. py −−cpu−type=MinorCPU −−caches−c ~/Desktop/gem5_test**

από το αρχείο stats.txt, που προκύπτει από την προσομοίωση βρίσκουμε :<br/>
Line 12: sim_seconds : 0.000041 // Number of seconds simulated

Αντίστοιχα για τονTimingSimpleCPU:

**./ build /ARM/gem5. opt −d ~/Desktop/TimingSimpleCPUdefault configs/example/ se. py −−cpu−type=TimingSimpleCPU −−caches−c ~/Desktop/gem5_test**

από το αρχείο stats.txt, που προκύπτει από την προσομοίωση βρίσκουμε :<br/>
Line 12: sim_seconds : 0.000048 // Number of seconds simulated

**b)**

Από τις προσομοιώσεις ο MinorCPU είναι πιο γρήγορος από τονTimingSimpleCPU. Αυτό ήταν αναμενόμενο καθώς ο MinorCPU υποστηρίζει 4 επίπεδα pipeline και τεχνολογία μνημών cache. Επίσης, όσον αφορά τους κύκλους που χρειάστηκαν για την ολοκλήρωση του προγράμματος στον TimingSimpleCPU είναι 96486 σε αντίθεση με τους 82664 κύκλους του MinorCPU. Διαφορά που οφείλεται στο ότι ο TimingSimpleCPU κάνει απευθείας προσπέλαση στην κύρια μνήμη που χρειάζεται περισσότερους κύκλους.

**c)**

 **1.Προσομοίωση σε συχνότητα επεξεργαστή 500MΗz**-> Πρόσθεση σαν option στην εντολή : **-–sys-clock = 500000000**,

από το stats.txt:<br/>
MinorCPU<br/>
Line 12: sim_seconds : 0.000049 // Number of seconds simulated<br/>
TimingSimpleCPU<br/>
Line 12: sim_seconds : 0.000055  // Number of seconds simulated<br/>

Βλέπουμε μια αύξηση του χρόνου εκτέλεσης που είναι απολύτως λογική, καθώς υποδιπλασιάζουμε την συχνότητα του ρολογιού οπότε ο χρόνος
κύκλου διπλασιάζεται.

**2.Προσομοίωση με αλλαγή τεχνολογίας μνήμης σε DDR4_2400_8x8** από την default DDR3_1600_8x8 -> Πρόσθεση σαν option στην εντολή :**--mem-type=DDR4_2400_8x8**.

από το stats.txt:<br/>
ο χρόνος στην περίπτωση του MinorCPU :<br/>
Line 12: sim_seconds : 0.000040 // Number of seconds simulated<br/>
ο χρόνος στην περίπτωση του TimingSimpleCPU :<br/>
Line 12: sim_seconds : 0.000048 // Number of seconds simulated<br/>

Παρατηρούμε μείωση του χρόνου εκτέλεσης γιατί τώρα στο σύστημα που εξομοιώνουμε, έχουμε μνήμες με μεγαλύτερο bandwidth και καλύτερης τεχνολογίας Double Data Rate.

##### **Κριτική Εργασίας**
Η πρώτη εργασία μας εξοικείωσε με πολλά θέματα αρχιτεκτονικής επεξεργαστών όπως cache accesses, ram technologies και εξομοιώσεις προγραμμάτων σε επεξεργαστή τύπου ARM γενικότερα. Αρκετά πράγματα που ειπώθηκαν στο μάθημα τα είδαμε και σε πιο πρακτικό επίπεδο.<br/>
H εξοικείωση μας εγινε σε πεδία όπως, η επαφή με το Linux, η χρήση διαδεδομένων εργαλείων για την ανάπτυξη κώδικα, cross compilation, εργαλεία αρχιτεκτονικής καθώς και η αναζήτηση πληροφοριών([το site του gem5](http://www.gem5.org/documentation/), gem5_rsk.pdf που ήταν οι κύριες πηγές μας). Κάποια από τα παραπάνω τα είδαμε για πρώτη φορά.<br/>
-Θετικό αποτέλεσε ότι ήταν ομαδική και υπήρχε πνεύμα συνεργασίας, οπότε μπορούσαμε να συζητάμε τα αποτελέσματα και να διασταυρώνουμε πληροφορίες.<br/>
-Στα ερωτήματα 2b) και 2c) θεωρούμε ότι καλό θα ήταν να δωθεί περαιτέρω διευκρίνηση και ελπίζουμε να αποσαφηνιστεί στο εργαστήριο.<br/>

edit: Αποσαφηνίστηκαν τα 2b,2c.

###### Πηγές - Βιβλιογραφία: 
- [gem5.org](https://www.gem5.org/ "gem5 Official Website")
- [Arm Research Starter Kit: System Modeling using gem5 by Ashkan Tousi and Chuan Zhu
July 2017 (updated October 2020)](https://raw.githubusercontent.com/arm-university/arm-gem5-rsk/master/gem5_rsk.pdf)


Τέλος αναφοράς.
