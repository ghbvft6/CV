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
public class school implements ListModel{
    private String name;
    //private Vector<course> courses;
    private Vector courses = new Vector();
    
    public school(String NAME){
        name = NAME;
    }
    
    public void addcourse(String NAME){
        courses.add(new course(NAME));
    }
    
    public void removecourse(int i){
        if(i<courses.size()) courses.remove(i);
    }
    
    public String getName(){
        return name;
    }
    
    public course getcourse(int i){
        if(i<courses.size()) return (course)courses.get(i);
        else return new course("");
    }
    
    public int getNumberOfcourses(){
        return courses.size();
    }
    
    public course findcourseByName(String NAME){
        int i = courses.size();
        while(i-->0){
            if(((course)courses.get(i)).getName().equals(NAME)){
                break;
            }
        }
        if(i>=0) return (course)courses.get(i);
        else return new course("");
    }
    
    public Object getElementAt(int index) {
        return courses.elementAt(index);
    }
    
    public int getSize() {
        return courses.size();
    }

    @Override
    public void addListDataListener(ListDataListener ll) {
//        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void removeListDataListener(ListDataListener ll) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public String toString() {
        return getName();
    }
}
