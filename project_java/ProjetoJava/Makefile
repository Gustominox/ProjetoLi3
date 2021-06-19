JAVAC = javac
CLASS_FILES = ./*.class
# view/*.class model/Businesses/*.class model/Reviews/*.class model/Users/*.class loaders/*.class

#Default: $(CLASS_FILES)

%.class: %.java
	$(JAVAC) -d out *.java

clean: 
	rm -r out

run: GestReviewsMVC.class
	java -cp out GestReviewsMVC
