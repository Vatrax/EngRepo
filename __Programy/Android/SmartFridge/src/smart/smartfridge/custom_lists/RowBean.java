package smart.smartfridge.custom_lists;

public class RowBean {
	 
	public String name;
    public String weight;
    public String maxweight;
    public String price;
    
    public RowBean(){
    	
    }
 
    public RowBean(String name, String weight, String maxweight, String price) {
 
        this.name = name;
        this.weight = weight;
        this.maxweight = maxweight;
        this.price = price;
        }
}