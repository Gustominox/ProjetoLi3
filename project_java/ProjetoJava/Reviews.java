/**
 * Escreva a descrição da classe Reviews aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */

import java.time.LocalDateTime;

public class Reviews
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
    
    public Reviews(){
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

    public Reviews(String reviewId, String userId, String businessId, float stars, int useful,
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

    public Reviews(Reviews rev){
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

    public Reviews clone(){
        return new Reviews(this);
    }
    
    public boolean equals(Object obj){
        if (obj == this) return true;
        if (obj == null || ! obj.getClass().equals(this.getClass())) return false;
        Reviews rev = (Reviews) obj;
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
