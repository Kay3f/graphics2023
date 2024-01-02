using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

[System.Serializable]
public struct ItemPrefab
{
    public Item item;
    public int itemHeld;
}

[CreateAssetMenu(fileName ="New Inventory",menuName = "Inventory/New Inventory")]
public class Inventory : ScriptableObject
{
    //[SerializeReference]
    //public Dictionary<Item, int> itemDic = new Dictionary<Item, int>();
    //public ItemPrefab[] ItemPrefabs;
    public List<ItemPrefab> ItemPrefabs = new List<ItemPrefab>();//��¼�ñ����еĲ�ͬ�������Ʒ
    
    private void Awake()
    {
        
    }

    void Start()
    {
        //ItemPrefabs = new ItemPrefab[100];
    }

    void Update()
    {
        
    }
}
