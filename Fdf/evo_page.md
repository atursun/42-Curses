### **Preliminaries**

**Preliminary tests**

Check the following points:

* The access conditions to the defence are respected (an empty repository, non functioning, a Norm error, cheating etc.).
* See above.
* No forbidden functions used. (Unless justified for a bonus).
* A functioning Makefile that contains the usual rules is present and only relinks when necessary.
* Presence after compilation of the binary fdf.
* No segfault, bus error, weird stuff.
* No memory leaks.

If any of this does not work, the defence stops here.

---

## **Features**

### **Error management**

Test fdf without parameters, with too many parameters, a non-existing file or on which you have no rights. If the management is correct, then it’s all good. This is the only error management we are asking for; during the rest of the defence the maps have to be formatted properly inside of the files.

---

### **Graphic**

Run the program with the 42 map given on the subject:

* A window opens
* Something is drawn in the window
* We can see a isometric projection of the 42 map
* Press ESC and cleanly get out of the program

---

### **Trace**

* Use a flat map with nothing but 0, sized 4x4. We have a flat wireframe grid with a projection that is used to give a 3D concept.
* Same map, with 1 point at a different altitude. Check that the result corresponds and that the 3D feel is present.

---

### **Heavy stuff**

* Check if the program handles a bigger map, and an aleatory map 16x16.

---

### **Heavier stuff**

Test with bigger maps, heavier, either from those given with the subject, or from your own.
Be logical and stay compatible between what could contain your map (colors for example) and what the program you are correcting can do.

---

### **Graphic responsive**

If during the last test, with heavy maps, graphics stay fluid and pleasant then it’s cool.

---

### **Image usage**

Check the code and see if the student is using the images from the minilibx to draw the image instead of putting pixel by pixel ;)


----


- nm -u fdf -> yasaklı funcs var mı ?
- relink -> Hiçbir dosya değişmemiş olmasına rağmen make komutu çalıştırıldığında hedef (target) yeniden derleniyorsa buna relink denir.
Program .o dosyalarına bağlı, .o dosyaları değişmediyse hedef de değişmez, Böylece make tekrar linkleme yapmaz

ÖNEMLİ
- dosya iznini değiştirdiğimizde çalışmaması gerekiyor onu kontrol et