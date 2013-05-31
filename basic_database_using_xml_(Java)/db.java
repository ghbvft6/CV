/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package xmldb;

import javax.swing.DefaultListModel;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/**
 *
 * @author Admin
 */
public class zad1 extends javax.swing.JFrame {
    school SCHOOL = new school("myschool");
    
    public void schooltoxml(school SCHOOL){
        DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder docBuilder = null;
        try {
            docBuilder = docFactory.newDocumentBuilder();
        } catch (ParserConfigurationException ex) {
            Logger.getLogger(zad1.class.getName()).log(Level.SEVERE, null, ex);
        }

        Document doc = docBuilder.newDocument();
        Element rootElement = doc.createElement(SCHOOL.toString());
        doc.appendChild(rootElement);
        
        int i = SCHOOL.getSize();
        while(i-->0){
            Element course = doc.createElement("course");
            rootElement.appendChild(course);

            course.setAttribute("id", SCHOOL.getElementAt(i).toString());

            int j = ((course)SCHOOL.getElementAt(i)).getSize();
            while(j-->0){
                Element student = doc.createElement("student");
                course.appendChild(student);

                student.setAttribute("id", ((course)SCHOOL.getElementAt(i)).getElementAt(j).toString());

                Element credit = doc.createElement("credit");
                credit.appendChild(doc.createTextNode(String.valueOf(((student)((course)SCHOOL.getElementAt(i)).getElementAt(j)).getCredit())));
                student.appendChild(credit);
            }
        }

        try {
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);
            StreamResult result = new StreamResult(new File("C:\\xml.xml"));

            transformer.transform(source, result);
        } catch (TransformerConfigurationException ex) {
            Logger.getLogger(zad1.class.getName()).log(Level.SEVERE, null, ex);
        } catch (TransformerException ex) {
            Logger.getLogger(zad1.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public void schoolfromxml(school SCHOOL){
        try {
            File fXmlFile = new File("C:\\xml.xml");
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(fXmlFile);
            doc.getDocumentElement().normalize();

            doc.getDocumentElement().getNodeName();
            
            NodeList courses = doc.getElementsByTagName("course");
            int i = 0;
            while(i< courses.getLength()){
                Node course_node = courses.item(i);
                
                if (course_node.getNodeType() == Node.ELEMENT_NODE) {
                    Element course = (Element) course_node;
                    SCHOOL.addcourse(course.getAttribute("id"));
                    
                    NodeList students = course.getElementsByTagName("student");
                    int j = 0;
                    while(j<students.getLength()){
                        Node student_node = students.item(j);
                        
                        if (student_node.getNodeType() == Node.ELEMENT_NODE) {
                            Element student = (Element) student_node;
                            ((course)SCHOOL.getElementAt(i)).addStudent(student.getAttribute("id"));

                            ((student)((course)SCHOOL.getElementAt(i)).getElementAt(j)).setCredit(Boolean.valueOf(student.getElementsByTagName("credit").item(0).getTextContent()));
                        }
                        ++j;
                    }
                }
                ++i;
            }

            // write the content into xml file
            try {
                TransformerFactory transformerFactory = TransformerFactory.newInstance();
                Transformer transformer = transformerFactory.newTransformer();
                DOMSource source = new DOMSource(doc);
                StreamResult result = new StreamResult(new File("C:\\xml.xml"));

                // Output to console for testing
                // StreamResult result = new StreamResult(System.out);

                transformer.transform(source, result);
            } catch (TransformerConfigurationException ex) {
                Logger.getLogger(zad1.class.getName()).log(Level.SEVERE, null, ex);
            } catch (TransformerException ex) {
                Logger.getLogger(zad1.class.getName()).log(Level.SEVERE, null, ex);
            }
        } catch (ParserConfigurationException ex) {
            Logger.getLogger(zad1.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SAXException ex) {
            Logger.getLogger(zad1.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(zad1.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    /**
     * Creates new form zad1
     */
    public zad1() {
        initComponents();
        course_list.setModel(SCHOOL);
        schoolfromxml(SCHOOL);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        course_add_btn = new javax.swing.JButton();
        course_del_btn = new javax.swing.JButton();
        student_add_btn = new javax.swing.JButton();
        student_del_btn = new javax.swing.JButton();
        course_spane = new javax.swing.JScrollPane();
        course_list = new javax.swing.JList();
        student_spane = new javax.swing.JScrollPane();
        student_list = new javax.swing.JList();
        course_label = new javax.swing.JLabel();
        student_label = new javax.swing.JLabel();
        passed_label = new javax.swing.JLabel();
        passed_yes_radio = new javax.swing.JRadioButton();
        passed_no_radio = new javax.swing.JRadioButton();
        course_edit = new javax.swing.JTextField();
        student_edit = new javax.swing.JTextField();
        save_btn = new javax.swing.JButton();
        course_add_btn1 = new javax.swing.JButton();
        student_add_btn1 = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        course_add_btn.setText("add");
        course_add_btn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                course_add_btnActionPerformed(evt);
            }
        });

        course_del_btn.setText("del");
        course_del_btn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                course_del_btnActionPerformed(evt);
            }
        });

        student_add_btn.setText("add");
        student_add_btn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                student_add_btnActionPerformed(evt);
            }
        });

        student_del_btn.setText("del");
        student_del_btn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                student_del_btnActionPerformed(evt);
            }
        });

        course_list.addListSelectionListener(new javax.swing.event.ListSelectionListener() {
            public void valueChanged(javax.swing.event.ListSelectionEvent evt) {
                course_listValueChanged(evt);
            }
        });
        course_spane.setViewportView(course_list);

        student_list.addListSelectionListener(new javax.swing.event.ListSelectionListener() {
            public void valueChanged(javax.swing.event.ListSelectionEvent evt) {
                student_listValueChanged(evt);
            }
        });
        student_spane.setViewportView(student_list);

        course_label.setText("course");

        student_label.setText("student");

        passed_label.setText("passed");

        passed_yes_radio.setText("yes");
        passed_yes_radio.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                passed_yes_radioActionPerformed(evt);
            }
        });

        passed_no_radio.setText("no");
        passed_no_radio.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                passed_no_radioActionPerformed(evt);
            }
        });

        save_btn.setText("save");
        save_btn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                save_btnActionPerformed(evt);
            }
        });

        course_add_btn1.setText("find");
        course_add_btn1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                course_add_btn1ActionPerformed(evt);
            }
        });

        student_add_btn1.setText("find");
        student_add_btn1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                student_add_btn1ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(course_spane, javax.swing.GroupLayout.PREFERRED_SIZE, 409, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(course_label))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(course_add_btn)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(course_edit, javax.swing.GroupLayout.PREFERRED_SIZE, 122, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(course_add_btn1)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(course_del_btn)
                                .addGap(61, 61, 61)))
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(student_spane, javax.swing.GroupLayout.DEFAULT_SIZE, 425, Short.MAX_VALUE)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(student_label)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(student_add_btn)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(student_edit, javax.swing.GroupLayout.PREFERRED_SIZE, 122, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(student_add_btn1)
                                        .addGap(70, 70, 70)
                                        .addComponent(student_del_btn)))
                                .addGap(0, 0, Short.MAX_VALUE))))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(345, 345, 345)
                        .addComponent(passed_yes_radio)
                        .addGap(18, 18, 18)
                        .addComponent(passed_label)
                        .addGap(18, 18, 18)
                        .addComponent(passed_no_radio)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(save_btn)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(course_label)
                    .addComponent(student_label))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(course_add_btn)
                    .addComponent(course_del_btn)
                    .addComponent(student_add_btn)
                    .addComponent(student_del_btn)
                    .addComponent(course_edit, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(student_edit, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(course_add_btn1)
                    .addComponent(student_add_btn1))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(course_spane, javax.swing.GroupLayout.DEFAULT_SIZE, 379, Short.MAX_VALUE)
                    .addComponent(student_spane))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(passed_label)
                    .addComponent(passed_no_radio)
                    .addComponent(passed_yes_radio)
                    .addComponent(save_btn))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void course_add_btnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_course_add_btnActionPerformed
        if(course_edit.getText().equals("")==false){
            SCHOOL.addcourse(course_edit.getText());
            course_list.setSelectedIndex(SCHOOL.getSize()-1);
            //student_list.setModel(SCHOOL.getcourse(0));
            course_list.updateUI();
        }
        //course_list.r
        // TODO add your handling code here:
    }//GEN-LAST:event_course_add_btnActionPerformed

    private void course_del_btnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_course_del_btnActionPerformed
        SCHOOL.removecourse(course_list.getSelectedIndex());
        course_list.updateUI();
        //if(SCHOOL.getSize()>0){
           // System.out.println(course_list.getSelectedIndex());
            //student_list.setModel((course)course_list.getSelectedValue());           
        //}else{
            course_list.setSelectedIndex(0);
            //student_list.setModel(new DefaultListModel());
        //}
        student_list.updateUI();
        // TODO add your handling code here:
    }//GEN-LAST:event_course_del_btnActionPerformed

    private void student_add_btnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_student_add_btnActionPerformed
        if(student_edit.getText().equals("")==false){
            ((course)course_list.getSelectedValue()).addStudent(student_edit.getText());
            student_list.updateUI();
        }
        // TODO add your handling code here:
    }//GEN-LAST:event_student_add_btnActionPerformed

    private void student_del_btnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_student_del_btnActionPerformed
        ((course)course_list.getSelectedValue()).removeStudent(student_list.getSelectedIndex());
        student_list.setSelectedIndex(0);
        student_list.updateUI();
        // TODO add your handling code here:
    }//GEN-LAST:event_student_del_btnActionPerformed

    private void course_listValueChanged(javax.swing.event.ListSelectionEvent evt) {//GEN-FIRST:event_course_listValueChanged
        student_list.setModel((course)course_list.getSelectedValue());
        // TODO add your handling code here:
    }//GEN-LAST:event_course_listValueChanged

    private void student_listValueChanged(javax.swing.event.ListSelectionEvent evt) {//GEN-FIRST:event_student_listValueChanged
        if(student_list.isSelectionEmpty()==false){
            if(((student)student_list.getSelectedValue()).getCredit()){
                passed_no_radio.setSelected(false);
                passed_yes_radio.setSelected(true);
            }else{
                passed_no_radio.setSelected(true);
                passed_yes_radio.setSelected(false);
            }
        }
        // TODO add your handling code here:
    }//GEN-LAST:event_student_listValueChanged

    private void passed_yes_radioActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_passed_yes_radioActionPerformed
        ((student)student_list.getSelectedValue()).setCredit(true);
        passed_no_radio.setSelected(false);
        passed_yes_radio.setSelected(true);
        // TODO add your handling code here:
    }//GEN-LAST:event_passed_yes_radioActionPerformed

    private void passed_no_radioActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_passed_no_radioActionPerformed
        ((student)student_list.getSelectedValue()).setCredit(false);
        passed_no_radio.setSelected(true);
        passed_yes_radio.setSelected(false);
        // TODO add your handling code here:
    }//GEN-LAST:event_passed_no_radioActionPerformed

    private void save_btnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_save_btnActionPerformed
        schooltoxml(SCHOOL);
        // TODO add your handling code here:
    }//GEN-LAST:event_save_btnActionPerformed

    private void course_add_btn1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_course_add_btn1ActionPerformed
        course_list.setSelectedValue(SCHOOL.findcourseByName(course_edit.getText()),true);
        // TODO add your handling code here:
    }//GEN-LAST:event_course_add_btn1ActionPerformed

    private void student_add_btn1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_student_add_btn1ActionPerformed
        student_list.setSelectedValue(((course)course_list.getSelectedValue()).findStudentByName(student_edit.getText()),true);
        // TODO add your handling code here:
    }//GEN-LAST:event_student_add_btn1ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(zad1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(zad1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(zad1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(zad1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new zad1().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton course_add_btn;
    private javax.swing.JButton course_add_btn1;
    private javax.swing.JButton course_del_btn;
    private javax.swing.JTextField course_edit;
    private javax.swing.JLabel course_label;
    private javax.swing.JList course_list;
    private javax.swing.JScrollPane course_spane;
    private javax.swing.JLabel passed_label;
    private javax.swing.JRadioButton passed_no_radio;
    private javax.swing.JRadioButton passed_yes_radio;
    private javax.swing.JButton save_btn;
    private javax.swing.JButton student_add_btn;
    private javax.swing.JButton student_add_btn1;
    private javax.swing.JButton student_del_btn;
    private javax.swing.JTextField student_edit;
    private javax.swing.JLabel student_label;
    private javax.swing.JList student_list;
    private javax.swing.JScrollPane student_spane;
    // End of variables declaration//GEN-END:variables
}
