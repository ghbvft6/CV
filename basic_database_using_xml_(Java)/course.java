/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package xmldb;

import java.util.Vector;
import javax.swing.ListModel;
import javax.swing.event.ListDataListener;

/**
 *
 * @author Admin
 */
public class course implements ListModel{
    private String name;
    //private Vector<student> students;
    private Vector students = new Vector();
    
    public course(String NAME){
        name = NAME;
    }
    
    public void addStudent(String NAME){
        students.add(new student(NAME));
    }
    
    public void removeStudent(int i){
        if(i<students.size()) students.remove(i);
    }
    
    public String getName(){
        return name;
    }
    
    public student getStudent(int i){
        if(i<students.size()) return (student)students.get(i);
        else return new student("");
    }
    
    public int getNumberOfStudents(){
        return students.size();
    }
    
    public student findStudentByName(String NAME){
        int i = students.size();
        while(i-->0){
            if(((student)students.get(i)).getName().equals(NAME)){
                break;
            }
        }
        if(i>=0) return (student)students.get(i);
        else return new student("");
    }
    
    public Object getElementAt(int index) {
        return students.elementAt(index);
    }
    
    public int getSize() {
        return students.size();
    }

    @Override
    public String toString() {
        return getName();
    }
    
    @Override
    public void addListDataListener(ListDataListener ll) {
//        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void removeListDataListener(ListDataListener ll) {
//        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
