import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

public class Review
{
    private String reviewId;
    private String userId;
    private String businessId;
    private float stars;
    private int useful;
    private int funny;
    private int cool;
    private LocalDateTime date;
    private String text;
    
    public Review(){
         this.reviewId = "";
         this.userId = "";
         this.businessId = "";
         this.stars = 0;
         this.useful = 0;
         this.funny = 0;
         this.cool = 0;
         this.date = LocalDateTime.now();
         this.text = "";
    }

    public Review(String reviewId, String userId, String businessId, float stars, int useful,
               int funny, int cool, LocalDateTime date, String text){
         this.reviewId = reviewId;
         this.userId = userId;
         this.businessId = businessId;
         this.stars = stars;
         this.useful = useful;
         this.funny = funny;
         this.cool = cool;
         this.date = date;
         this.text = text;
    }

    public Review(Review rev){
         this.reviewId = rev.getReviewId();
         this.userId = rev.getUserId();
         this.businessId = rev.getBusinessId();
         this.stars = rev.getStars();
         this.useful = rev.getUseful();
         this.funny = rev.getFunny();
         this.cool = rev.getCool();
         this.date = rev.getDate();
         this.text = rev.getText();
    }

    /**
     * Construtor que cria um objeto User a partir de uma linha do ficheiro com os campos divididos.
     */
    public Review(String[] info){
        try{
            addReview(info);
        }
        catch(ReviewNotValidException e){
            System.out.println("Ocorreu um erro! Review não é válido");
            new Review();
        }
    }
    
    public String getReviewId(){
        return this.reviewId;
    }

    public String getUserId(){
        return this.userId;
    }

    public String getBusinessId(){
        return this.businessId;
    }

    public float getStars(){
        return this.stars;
    }

    public int getUseful(){
        return this.useful;
    }

    public int getFunny(){
        return this.funny;
    }

    public int getCool(){
        return this.cool;
    }

    public LocalDateTime getDate(){
        return this.date;
    }

    public String getText(){
        return this.text;
    }
    
    public void setReviewId(String reviewId){
        this.reviewId = reviewId;
    }

    public void setUserId(String userId){
        this.userId = userId;
    }

    public void setBusinessId(String businessId){
        this.businessId = businessId;
    }

    public void setStars(float stars){
        this.stars = stars;
    }

    public void setUseful(int useful){
        this.useful = useful;
    }

    public void setFunny(int funny){
        this.funny = funny;
    }

    public void setCool(int cool){
        this.cool = cool;
    }

    public void setDate(LocalDateTime date){
        this.date = date;
    }

    public void setText(String text){
        this.text = text;
    }

    /**
     * Método que constrói um objeto Review, caso todos os campos sejam válidos.
     */
    public void addReview(String[] info) throws ReviewNotValidException{
        int i;
        if(info[0].length() == 22){
            this.reviewId = info[0];
        }
        else{
            throw new ReviewNotValidException(info[0]);
        }
        
        if(info[1].length() == 22){
            this.userId = info[1];
        }
        else{
            throw new ReviewNotValidException(info[1]);
        }
        
        if(info[2].length() == 22){
            this.businessId = info[2];
        }
        else{
            throw new ReviewNotValidException(info[1]);
        }
        
        float starsToFloat = Float.parseFloat(info[3]);
        if(starsToFloat >= 1.0 && starsToFloat <= 5.0){
            this.stars = starsToFloat;
        }
        else{
            throw new ReviewNotValidException(info[3]);
        }
        
        int usefulToInt = Integer.parseInt(info[4]);
        if(usefulToInt >= 0){
            this.useful = usefulToInt;
        }
        else{
            throw new ReviewNotValidException(info[4]);
        }
        
        int funnyToInt = Integer.parseInt(info[5]);
        if(funnyToInt >= 0){
            this.funny = funnyToInt;
        }
        else{
            throw new ReviewNotValidException(info[5]);
        }
        
        int coolToInt = Integer.parseInt(info[6]);
        if(coolToInt >= 0){
            this.cool = coolToInt;
        }
        else{
            throw new ReviewNotValidException(info[6]);
        }
        
        if(info[7] != null){
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            this.date = LocalDateTime.parse(info[7], formatter);
        }
        else{
            throw new ReviewNotValidException(info[7]);
        }
        this.text = info[8];
    }
    
        public static String[] parse(String info){
        String[] camposReview = info.split(";");
        return camposReview;
    }
    
    public Review clone(){
        return new Review(this);
    }
    
    public boolean equals(Object obj){
        if (obj == this) return true;
        if (obj == null || ! obj.getClass().equals(this.getClass())) return false;
        Review rev = (Review) obj;
        return  this.reviewId.equals(rev.getReviewId()) &&
            this.userId.equals(rev.getUserId())&&
            this.businessId.equals(rev.getBusinessId()) &&
            this.stars == rev.getStars() &&
            this.useful == rev.getUseful() &&
            this.funny == rev.getFunny() &&
            this.cool == rev.getCool() &&
            this.date == rev.getDate() &&
            this.text.equals(rev.getText());
    }
    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Review ID: ").append(this.reviewId);
        sb.append("User ID: ").append(this.userId);
        sb.append("Business ID: ").append(this.businessId);
        sb.append("Stars: ").append(this.stars);
        sb.append("Useful: ").append(this.useful);
        sb.append("Funny: ").append(this.funny);
        sb.append("Cool: ").append(this.cool);
        sb.append("Date: ").append(this.date);
        sb.append("Text: ").append(this.text);
        return sb.toString();
    }
}
