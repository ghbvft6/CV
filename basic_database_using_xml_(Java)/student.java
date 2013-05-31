/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package xmldb;

/**
 *
 * @author Admin
 */
public class student {
    private String name;
    private boolean passed;
    
    public student(String NAME){
        name = NAME;
        passed = false;
    }
    
    public String getName(){
        return name;
    }
    
    public void setCredit(boolean PASSED){
        passed = PASSED;
    }
    
    public boolean getCredit(){
        return passed;
    }
    
    @Override
    public String toString() {
        return getName();
    }
}
