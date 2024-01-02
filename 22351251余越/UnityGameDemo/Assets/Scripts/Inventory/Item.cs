using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//��Ʒ����
public enum ItemType
{
    WEAPON,//����
    HAT,//ñ��
    RING,//��ָ
    BOOK,//�鱾
    CONSUME,//ҩˮ������Ʒ
    ALL//������Ʒ���ͣ���������Ʒ����ƷҪ��
}

[CreateAssetMenu(fileName ="New Item",menuName ="Inventory/New Item")]
public class Item : ScriptableObject
{
    public string itemName;
    public Sprite itemImage;
    //public List<Item> itemPlayerHeld = new List<Item>();
    [TextArea]
    public string itemInfo;
    //public int itemHeld = 1;
    public GameObject itemGOPrefab;
    public ItemType itemType;
    [Header("ItemData")]
    public int atkPlus;
    public int spPlus;
    public float criticalChancePlus;
    public float criticalMagicChancePlus;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
